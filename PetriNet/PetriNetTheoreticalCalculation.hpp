#pragma once
#include "PetriNet.hpp"
namespace pn {
	size_t factorial(size_t i) {
		for (size_t c = i - 1; c >= 1; c--)
			i *= c;
		return i;
	}
	template <typename TaskType> class PetriNetTheoreticalCalculation {
	private:
		static size_t number_of_states;
		static std::vector<std::shared_ptr<PetriNet<TaskType>>> current;
		static std::vector<std::vector<size_t>> arrayState;
		static size_t existingStates;
		static std::vector<std::vector<float>> intensity;
		static std::vector<float> probability;
	public:
		static std::vector<std::pair<std::string, float>> calculate(std::vector<std::shared_ptr<PetriNet<TaskType>>> nets, std::vector<TaskType> tasks);
		static void distribution(size_t index_of_state);
		static void calcMoves(size_t task, size_t state);
		static void makeMove(int oldIndex, int newIndex, int state, double probability);
		static void linearSystem();
		static float getDelta(std::vector<std::vector<float>> system_input);
		static std::vector<std::pair<std::string, float>> generateResults();
	};
}
template<typename TaskType>
size_t pn::PetriNetTheoreticalCalculation<TaskType>::number_of_states = 0ull;
template<typename TaskType>
std::vector<std::shared_ptr<pn::PetriNet<TaskType>>> pn::PetriNetTheoreticalCalculation<TaskType>::current = {};
template<typename TaskType>
std::vector<std::vector<size_t>> pn::PetriNetTheoreticalCalculation<TaskType>::arrayState = {};
template<typename TaskType>
size_t pn::PetriNetTheoreticalCalculation<TaskType>::existingStates = 0ull;
template<typename TaskType>
std::vector<std::vector<float>> pn::PetriNetTheoreticalCalculation<TaskType>::intensity = {};
template<typename TaskType>
std::vector<float> pn::PetriNetTheoreticalCalculation<TaskType>::probability = {};
template<typename TaskType>
inline std::vector<std::pair<std::string, float>> pn::PetriNetTheoreticalCalculation<TaskType>::calculate(std::vector<std::shared_ptr<PetriNet<TaskType>>> nets, std::vector<TaskType> tasks) {
	current = nets;
	for (auto &it : nets)
		it->clear();
	for (auto it : tasks)
		nets.front()->insert(it);

	number_of_states = factorial(nets.size() + tasks.size() - 1) / factorial(tasks.size()) / factorial(nets.size() - 1);
	arrayState.resize(nets.size());
	for (auto &it : arrayState)
		it.resize(number_of_states * 3);
	intensity.resize(number_of_states);
	for (auto &it : intensity)
		it.resize(number_of_states);
	probability.resize(number_of_states);

	arrayState[0][2] = 1;
	arrayState[1][0] = nets.size() - 1;
	arrayState[1][1] = 1;
	for (size_t i = 2; i < current.size(); i++)
		arrayState[i][2] = 1;
	existingStates++;
	size_t i = 0;
	do
		distribution(i++);
	while (i < existingStates);
	linearSystem();
	return generateResults();
}
template<typename TaskType>
inline void pn::PetriNetTheoreticalCalculation<TaskType>::distribution(size_t index_of_state) {
	for (int i = 0; i < current.size(); i++)
		if (arrayState[i][3 * index_of_state + 1] == 1)
			calcMoves(i, index_of_state);
}
template<typename TaskType>
inline void pn::PetriNetTheoreticalCalculation<TaskType>::calcMoves(size_t task, size_t state) {
	for (auto &it : current[task]->transitions()) {
		auto temp = std::find_if(current.begin(), current.end(), [it](std::shared_ptr<PetriNet<TaskType>> &net) -> bool {
			return *it.first == *net;
		});
		if (temp == current.end())
			throw std::exception("Link to unexisting net was established.");
		makeMove(task, std::distance(current.begin(), temp), state, it.second);
	}
}
template<typename TaskType>
inline void pn::PetriNetTheoreticalCalculation<TaskType>::makeMove(int oldIndex, int newIndex, int state, double probability) {
	std::vector<std::vector<size_t>> system;
	system.resize(current.size());
	for (auto &it : system)
		it.resize(3);
	for (int i = 0; i < current.size(); i++)
		std::copy(arrayState[i].begin() + 3 * state, arrayState[i].begin() + 3 * state + 3, system[i].begin());
	system[oldIndex][1]--;
	system[oldIndex][2]++;
	system[newIndex][0]++;
	if ((system[oldIndex][0] > 0) & (system[oldIndex][2] == 1)) {
		system[oldIndex][0]--;
		system[oldIndex][2]--;
		system[oldIndex][1]++;
	}
	if ((system[newIndex][0] > 0) & (system[newIndex][2] == 1)) {
		system[newIndex][0]--;
		system[newIndex][2]--;
		system[newIndex][1]++;
	}
	size_t matches = 0;
	size_t newState = -1;
	for (int c = 0; c < existingStates; c++) {
		bool equals = true;
		for (int i = 0; i < current.size(); i++)
			for (int j = 0; j < 3; j++)
				if (arrayState[i][3 * c + j] != system[i][j]) {
					equals = false;
					break;
				}
		if (equals) {
			matches++;
			newState = c;
			break;
		}
	}
	if (matches == 0) {
		for (int i = 0; i < current.size(); i++)
			std::copy(arrayState[i].begin() + 3 * existingStates, arrayState[i].begin() + 3 * existingStates + 3, system[i].begin());
		newState = existingStates;
		existingStates++;
	}
	if (state != newState) {
		intensity[state][state] -= probability / current[oldIndex]->tau();
		intensity[newState][state] += probability / current[oldIndex]->tau();
	}
}
template<typename TaskType>
inline void pn::PetriNetTheoreticalCalculation<TaskType>::linearSystem() {
	std::vector<std::vector<float>> main_system;
	main_system.resize(number_of_states);
	for (auto &it : main_system)
		it.resize(number_of_states);
	for (int i = 0; i < current.size(); i++)
		std::copy(intensity[i].begin(), intensity[i].end(), main_system[i].begin());
	for (int i = 0; i < number_of_states; i++) 
		main_system[0][i] = 1;
	
	double main_delta = getDelta(main_system);
	std::vector<std::vector<float>> system;
	system.resize(number_of_states);
	for (auto &it : system)
		it.resize(number_of_states);

	std::vector<float> delta;
	delta.resize(number_of_states);

	size_t time = 0;
	size_t per;
	for (size_t i = 0; i < number_of_states; i++) {
		for (size_t j = 0; j < number_of_states; j++)
			std::copy(main_system[j].begin(), main_system[j].end(), system[j].begin());
		for (size_t j = 1; j < number_of_states; j++)
			system[j][i] = 0;
		delta[i] = getDelta(system);
		probability[i] = delta[i] / main_delta;
		if (float(i) / number_of_states > float(time + 1) / 20)
			per = ((time++) + 1) * 5;
	}
}
template<typename TaskType>
inline float pn::PetriNetTheoreticalCalculation<TaskType>::getDelta(std::vector<std::vector<float>> system_input) {
	float delta = 1.f;
	std::vector<std::vector<float>> system;
	system.resize(number_of_states);
	for (auto &it : system)
		it.resize(number_of_states);
	for (size_t i = 0; i < number_of_states; i++)
		std::copy(system_input[i].begin(), system_input[i].end(), system[i].begin());

	for (size_t i = 0; i < number_of_states - 1; i++) {
		if (system[i][i] == 0)
			for (size_t j = i + 1; j < number_of_states; j++)
				if (system[j][i] != 0) {
					for (size_t k = i; k < number_of_states; k++) {
						float temp = system[j][k];
						system[j][k] = system[i][k];
						system[i][k] = temp;
					}
					break;
				}
		if (system[i][i] != 0)
			for (size_t j = i + 1; j < number_of_states; j++) {
				float temp = system[j][i] / system[i][i];
				for (size_t k = i; k < number_of_states; k++)
					system[j][k] -= system[i][k] * temp;
			}
	}
	return delta;
}
template<typename TaskType>
inline std::vector<std::pair<std::string, float>> pn::PetriNetTheoreticalCalculation<TaskType>::generateResults() {
	std::vector<std::pair<std::string, float>> ret;
	ret.resize(current.size());
	for (size_t i = 0; i < ret.size(); i++)
		ret[i].first = current[i]->name();
	for (size_t i = 0; i < current.size(); i++)
		for (size_t j = 0; j < number_of_states; j++)
			if (arrayState[i][3 * j + 1] == 1)
				ret[i].second += probability[j];
	return ret;
}