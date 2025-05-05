#ifndef GUNUI_H_
#define GUNUI_H_

#include "game_object.h"

namespace game {

    class GunUi : public GameObject {
    public:
        
        GunUi(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint gunOne, GLuint gunTwo);
        GLuint getFirstGun() const { return FirstGun;}
        GLuint getSecondGun() const { return SecondGun; }

        void gunSwap();

        void Update(double delta_time) override;
    private:
        GLuint FirstGun;
        GLuint SecondGun;
    };

} // namespace game
#endif // BANDIT_ENEMY_H_
