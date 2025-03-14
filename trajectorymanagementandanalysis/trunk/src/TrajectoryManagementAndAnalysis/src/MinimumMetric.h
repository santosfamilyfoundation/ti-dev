#ifndef MINIMUMMETRIC_H_
#define MINIMUMMETRIC_H_

#include "Metric.h"

#include "TrajectoryExceptions.h"

/**
 * MinimumMetric class.
 *
 * The Minimum metric measures the similarity between two trajectories.
 * This class represents the smallest distance all 3 dimensions, for ALL points.
 * 
 */
template<typename Tr, typename To>
class MinimumMetric: public Metric<Tr, To>
{
public:
	/**
	 * Compute similarity between two trajectories.
	 *
	 * @param[in] a input trajectory
	 * @param[in] b input trajectory
	 * @param[out] result distance between two trajectories
	 */
  void distance(const Trajectory<Tr> *a, const Trajectory<Tr> *b, To &result, unsigned int nbOfPoints = std::numeric_limits<unsigned int>::max()) 
	{
		result = To(0);

		if (nbOfPoints == std::numeric_limits<unsigned int>::max())
		  checkTrajectoryLength(a->size(), b->size());

		To diff = abs((a->getPoint(0) - b->getPoint(0)).x);//est-ce que ça fait vraiment une différence de x ?
		for (unsigned int i = 0; i < a->size() and i < nbOfPoints; ++i)
		{
			cv::Point3_<typeof(static_cast<Tr>(a->getPoint(i)).x)> p(a->getPoint(i) - b->getPoint(i));
			diff = std::min(diff, abs(p.x));
			diff = std::min(diff, abs(p.y));
			if (dim(a->getPoint(i)) == 3)
			{
			  diff = std::min(diff, abs(p.z));
			}
		}

		result = diff;
	}

private:
	/**
	 * Check the length of the trajectories.
	 *
	 * @param[in] a the size of the trajectory
	 * @param[in] b the size of the trajectory
	 */
	void checkTrajectoryLength(size_t a, size_t b) const
	{
		if (a != b || a == 0)
		{
			throw TrajectoryLengthErrorException();
		}
	}
};

#endif /* MINIMUMMETRIC_H_ */
