#pragma once
namespace qs {
	class Statistics {
	protected:
		float m_lambda;
		float m_mu;
		float m_tau;
	public:
		Statistics(float lambda = 0.f, float mu = 0.f, float tau = 0.f);
		~Statistics();

		inline float lambda() const { return m_lambda; }
		inline float mu() const { return m_mu; }
		inline float tau() const { return m_tau; }
	};

	class ImitationStatistics : public Statistics {
	public:
		using Statistics::Statistics;
	};
}