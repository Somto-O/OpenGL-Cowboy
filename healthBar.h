#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#include "game_object.h"
#include "gunUi.h"
#include "text_game_object.h"
#include "player_game_object.h"
#include  <GLFW/glfw3.h>

namespace game {

    class HealthBar : public GameObject{
    public:
        HealthBar(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture,GunUi* guns, TextGameObject* t, PlayerGameObject* p, TextGameObject* s, TextGameObject* SCORE, TextGameObject* Time);

        void Update(double delta_time) override;
    private:
        GunUi* gunPic;
        TextGameObject* healthpoints;
        PlayerGameObject* player;
        TextGameObject* scorepoints;
        TextGameObject* ScoreWord;
        TextGameObject* Time_;
        double Start;
    };
    


} // namespace game
#endif // BANDIT_ENEMY_H_
