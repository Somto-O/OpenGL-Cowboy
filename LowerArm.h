#ifndef LOWERARM_H_
#define LOWERARM_H_

#include <iostream>


#include "UpperArm.h"


namespace game {

	class LowerArm : public GameObject
	{
	public:
		LowerArm(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, UpperArm* origin);



		// Update function for any special collectible object updates
		void Update(double delta_time) override;
		bool getSide() const { return side_; }

	private:
		UpperArm* origin_;
		bool side_;
		glm::vec3 spot_;

	};
} // namespace game

#endif 