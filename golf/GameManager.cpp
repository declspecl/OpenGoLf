#include "GameManager.h"

GameManager::GameManager(Shader* shaderProgram, float* deltaTime, GameObject2D& ball, GameObject2D& hole, GameObject2D& endText)
	: deltaTime(deltaTime)
	, shaderProgram(shaderProgram)
	, GS(GameState::MENU)
	, level(6)
	, ball(ball)
	, hole(hole)
	, endText(endText)
	, showEnd(false)
{
}

void GameManager::addObstacle(float x, float y, float z, float width, float height, float scaleX, float scaleY)
{
	this->obstacles.push_back(std::pair<GameObject2D*, Texture*>(new GameObject2D(x, y, z, width, height, this->deltaTime), new Texture("obstacle.png", true)));
	this->obstacles.back().first->scaleX = scaleX;
	this->obstacles.back().first->scaleY = scaleY;
}

void GameManager::clearObstacles()
{
	int size = this->obstacles.size();
	for (int i = 0; i < size; i++)
	{
		delete this->obstacles.back().first;
		delete this->obstacles.back().second;
		this->obstacles.pop_back();
	}
}

void GameManager::renderObstacles()
{
	for (int i = 0; i < this->obstacles.size(); i++)
	{
		this->obstacles[i].second->bindTexture();
		this->obstacles[i].first->setPos(this->obstacles[i].first->x, this->obstacles[i].first->y, 0.0f);
		this->obstacles[i].first->scaleHybrid(glm::vec3(this->obstacles[i].first->scaleX, this->obstacles[i].first->scaleY, 1.0f));
		this->shaderProgram->setFloat("opacity", this->obstacles[i].first->opacity);
		this->shaderProgram->setMatrix4fv("view", 1, GL_FALSE, glm::value_ptr(this->obstacles[i].first->viewMatrix));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0x00);
	}
}

void GameManager::loadLevel(int levelNum)
{
	ball.opacity = 1.0f;
	this->clearObstacles();
	this->GS = GameState::AIMING;

	switch (levelNum)
	{
	case 1:
		this->ball.setPos(0.0f, -0.55f, 0.0f);
		this->hole.setPos(0.0f, 0.725f, 0.0f);
		break;

	case 2:
		this->ball.setPos(0.0f, -0.55f, 0.0f);
		this->hole.setPos(0.0f, 0.725f, 0.0f);
		this->addObstacle(0.55f, 0.0f, 0.0f, 0.06f, 0.06f, 5.0f, 5.0f);
		this->addObstacle(-0.55f, 0.0f, 0.0f, 0.06f, 0.06f, 5.0f, 5.0f);
		break;

	case 3:
		this->ball.setPos(0.55f, -0.55f, 0.0f);
		this->hole.setPos(-0.545f, 0.545f, 0.0f);
		this->addObstacle(0.0f, 0.0f, 0.0f, 0.06, 0.06f, 5.0f, 5.0f);
		this->addObstacle(0.725f, 0.2f, 0.0f, 0.06, 0.06f, 5.0f, 5.0f);
		this->addObstacle(-0.725f, -0.2f, 0.0f, 0.06, 0.06f, 5.0f, 5.0f);
		break;

	case 4:
		this->ball.setPos(-0.55f, -0.55f, 0.0f);
		this->hole.setPos(0.545f, 0.545f, 0.0f);
		this->addObstacle(0.0f, 0.0f, 0.0f, 0.06, 0.06f, 7.0f, 7.0f);
		this->addObstacle(0.0f, .615f, 0.0f, 0.06, 0.06f, 7.5f, 10.0f);
		this->addObstacle(0.0f, -.615f, 0.0f, 0.06, 0.06f, 7.5f, 10.0f);
		this->addObstacle(0.545f, 0.0f, 0.0f, 0.06, 0.06f, 5.0f, 5.0f);
		this->addObstacle(-0.545f, 0.0f, 0.0f, 0.06, 0.06f, 5.0f, 5.0f);
		break;

	case 5:
		this->ball.setPos(0.725f, 0.725f, 0.0f);
		this->hole.setPos(0.7275f, -0.7275f, 0.0f);
		this->addObstacle(0.825f, 0.0f, 0.0f, 0.06f, 0.06f, 5.0f, 5.0f);
		this->addObstacle(0.5f, 0.0f, 0.0f, 0.06f, 0.06f, 5.0f, 5.0f);
		this->addObstacle(0.175f, 0.0f, 0.0f, 0.06f, 0.06f, 5.0f, 5.0f);
		this->addObstacle(0.175f, -0.525f, 0.0f, 0.06f, 0.06f, 5.0f, 5.0f);
		this->addObstacle(0.175f, 0.55f, 0.0f, 0.06f, 0.06f, 5.0f, 5.0f);
		this->addObstacle(-0.475f, 0.0f, 0.0f, 0.06f, 0.06f, 10.0f, 10.0f);
		break;

	case 6:
		showEnd = true;
		ball.setPos(0.0f, 0.0f, 0.0f);
		hole.setPos(1.5f, 1.5f, 0.0f);
		break;
	}
}