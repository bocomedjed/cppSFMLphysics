/*#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
//#include <bits/stdc++.h> // kao samo za kompetitivno programiranje, fuj
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
using namespace sf;

struct Ball {

    CircleShape circle;
    Vector2f velocity;
    float bounceFactor;

    Ball(float x,float y,  float bF){

        this->circle.setFillColor(Color::Black);
        this->circle.setOutlineColor(Color::White);
        this->circle.setOutlineThickness(1);
        this->circle.setRadius(15.f);
        this->circle.setOrigin(Vector2f(15.f,15.f));
        this->circle.setPosition(Vector2f(x,y));
        this->bounceFactor=bF;

    }

    void applyGravity(float dt){

        velocity.y += 980.f * dt;

    }

    void update(float dt){

        this->circle.move(velocity*dt);

    }
    void setVelocity(float velocityX, float velocityY){

        velocity = Vector2f(velocityX,velocityY);

    }

    void setBounceFactor(float x){

        bounceFactor = x;

    }

    void handleWallCCD(float dt) {
        float width = 800.f;
        float height = 600.f;
        float r = circle.getRadius();
        float wallFriction = 0.9f;

        // Horizontal walls
        if (circle.getPosition().x - r <= 0 && velocity.x < 0) velocity.x = -velocity.x * bounceFactor;
        if (circle.getPosition().x + r >= width && velocity.x > 0) velocity.x = -velocity.x * bounceFactor;
        // optionally apply friction
        velocity.y *= wallFriction;

        // Vertical walls
        if (circle.getPosition().y - r <= 0 && velocity.y < 0) velocity.y = -velocity.y * bounceFactor;
        if (circle.getPosition().y + r >= height && velocity.y > 0) velocity.y = -velocity.y * bounceFactor;
        // optionally apply friction
        velocity.x *= wallFriction;
}



    void handleBallCollision(Ball& other) {
        Vector2f delta = circle.getPosition() - other.circle.getPosition();
        float dist = sqrt(delta.x*delta.x + delta.y*delta.y);
        float combinedRadius = circle.getRadius() + other.circle.getRadius();

        if(dist < combinedRadius && dist > 0.f) {
            Vector2f normal = delta / dist;
            Vector2f relVel = velocity - other.velocity;
            float velAlongNormal = relVel.x*normal.x + relVel.y*normal.y;

            if(velAlongNormal > 0) return;

            float impulse = -(1 + bounceFactor) * velAlongNormal / 2.f;
            Vector2f impulseVec = impulse * normal;

            velocity -= impulseVec;
            other.velocity += impulseVec;
    }
}


};


int main()
{

    //IDEJE:GameLog,HighScore koji se cuva dok je otvoren prozor

    RenderWindow window(VideoMode({800, 600}), "Gravity ball");
    window.setFramerateLimit(60);
    vector<Ball> balls;

    float onClickBounce=500.f;
    const double dragFriction=0.99;
    int clickCounter=0;
    Font font;
    if (!font.openFromFile("bgothm.ttf")) {
        cerr << "Failed to load font\n";
        return 1;
    }
    string cc=to_string(clickCounter);
    Text text(font,"Broj klikova: ",30);
    text.setFillColor(Color::Cyan);
    text.setPosition(Vector2f(10.f,5.f));
    Text text2(font,"Igraj se matori",30);
    text2.setFillColor(Color::Red);
    text2.setPosition(Vector2f(10.f,35.f));
    Clock clock;
    float spawnTimer = 0.f;
    const float spawnDelay = 0.5f;   // seconds between balls
    int spawnedBalls = 0;
    int totalBalls = 5;
    while (window.isOpen()){

        float dt = clock.restart().asSeconds();// frame time
        spawnTimer += dt;
        if (spawnedBalls < totalBalls && spawnTimer >= spawnDelay){
            balls.emplace_back(0.f, 250.f + spawnedBalls * 12.f, 0.7f);
            balls.back().setVelocity(300.f, 0.f);
            spawnTimer = 0.f;
            spawnedBalls++;
        }

        while (auto event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
            int ballNumber=0;
            for(Ball& ball: balls){
                ballNumber++;
                if (auto* m = event->getIf<Event::MouseButtonPressed>()) {
                    clickCounter+=1;
                    string cc=to_string(clickCounter);
                    text.setString("Broj klikova: " + cc);
                    Vector2f circlePos = ball.circle.getPosition();
                    float radius=ball.circle.getRadius();
                    float dx=m->position.x-(circlePos.x+radius);
                    float dy=m->position.y-(circlePos.y+radius);
                    if(clickCounter>=10){
                        ball.setBounceFactor(0.3f);
                        text2.setString("Hehe, nakon 10. klika se smanjuje skocnost");
                    }
                    if (m->button == Mouse::Button::Left && dx*dx+dy*dy<radius*radius){
                        cout << "Click number " << clickCounter << " is on the ball number " << ballNumber << " at " << m->position.x << ", " << m->position.y << "\n";
                        float radius = ball.circle.getRadius();

                        float cx = circlePos.x;
                        float cy = circlePos.y;

                        float mx = m->position.x;
                        float my = m->position.y;

                        float dx = mx - cx;
                        float dy = my - cy;

                        float velocityx = (-dx * onClickBounce)*0.1;
                        float velocityy = (-dy * onClickBounce)*0.1;

                        ball.setVelocity(velocityx,velocityy);
                    }
                    else{
                        cout<< "Click number " << clickCounter << " is useless" << endl;
                    }
                }
            }
        }

        // --- Handle wall collisions (CCD) ---
        for (Ball& ball : balls){
            ball.applyGravity(dt);
            ball.handleWallCCD(dt);
        }
        // --- Handle ball-ball collisions ---
        for (int i = 0; i < balls.size() - 1; i++) {
            for (int j = i + 1; j < balls.size(); j++)
                balls[i].handleBallCollision(balls[j]);
        }

        for(Ball& ball: balls){
            ball.update(dt);
        }

        window.clear();
        window.draw(text);
        window.draw(text2);

        for(Ball& ball: balls){

            window.draw(ball.circle);

        }

        window.display();
    }

    return 0;
}
*/
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
using namespace sf;

struct Ball {
    CircleShape circle;
    Vector2f velocity;
    float bounceFactor;

    Ball(float x, float y, float bF) {
        circle.setRadius(35.f);
        circle.setOrigin(Vector2f(35.f, 35.f));
        circle.setFillColor(Color::Black);
        circle.setOutlineColor(Color::White);
        circle.setOutlineThickness(1);
        circle.setPosition(Vector2f(x, y));
        bounceFactor = bF;
        velocity = Vector2f(0.f, 0.f);
    }

    void applyGravity(float dt) {
        velocity.y += 980.f * dt; // gravity
    }

    void update(float dt) {
        circle.move(velocity * dt);
    }

    void handleWallCCD() {
        float r = circle.getRadius();
        float width = 800.f, height = 600.f;
        float wallFriction = 0.9999f;

        // Horizontal walls
        if (circle.getPosition().x - r < 0 && velocity.x < 0) velocity.x = -velocity.x * bounceFactor;
        else if (circle.getPosition().x + r > width && velocity.x > 0) velocity.x = -velocity.x * bounceFactor;

        // Vertical walls
        if (circle.getPosition().y - r < 0 && velocity.y < 0) velocity.y = -velocity.y * bounceFactor;
        else if (circle.getPosition().y + r > height && velocity.y > 0) velocity.y = -velocity.y * bounceFactor;

        // Apply simple friction along the perpendicular axis
        velocity.x *= wallFriction;
        velocity.y *= wallFriction;
    }

    void handleBallCollision(Ball& other) {
        Vector2f delta = circle.getPosition() - other.circle.getPosition();
        float dist = sqrt(delta.x*delta.x + delta.y*delta.y);
        float combinedRadius = circle.getRadius() + other.circle.getRadius();

        if (dist < combinedRadius && dist > 0.f) {
            Vector2f normal = delta / dist;
            Vector2f relVel = velocity - other.velocity;
            float velAlongNormal = relVel.x * normal.x + relVel.y * normal.y;

            if (velAlongNormal > 0) return; // balls are separating, no impulse needed

            // Optional: scale impulse down for less aggressive collisions
            float impulseFactor = 0.3f; // tweak between 0.3-0.7 for smoothness

            float impulse = -impulseFactor * (1 + bounceFactor) * velAlongNormal;
            float maxImpulse = 100.f; // tweak based on your scale
            if (abs(impulse) > maxImpulse) impulse = (impulse > 0 ? maxImpulse : -maxImpulse);
            Vector2f impulseVec = impulse * normal;

            // Apply velocity change only
            velocity -= impulseVec;
            other.velocity += impulseVec;
        }
    }

    void setVelocity(float vx, float vy) {
        velocity = Vector2f(vx, vy);
    }
};

int main() {
    RenderWindow window(VideoMode({800, 600}), "Gravity Ball SFML 3");
    window.setFramerateLimit(60);

    vector<Ball> balls;
    Clock clock;

    float spawnTimer = 0.f;
    const float spawnDelay = 0.5f; // spawn every 0.5s
    int spawnedBalls = 0;
    int totalBalls = 5;

    float onClickBounce = 500.f;
    int clickCounter = 0;

    Font font;
    if (!font.openFromFile("bgothm.ttf")) {
        cerr << "Failed to load font\n";
        return 1;
    }

    Text text(font, "Broj klikova: 0", 30);
    text.setFillColor(Color::Cyan);
    text.setPosition(Vector2f(10.f, 5.f));

    Text text2(font, "Igraj se matori", 30);
    text2.setFillColor(Color::Red);
    text2.setPosition(Vector2f(10.f, 35.f));

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        spawnTimer += dt;

        // Spawn balls safely
        if (spawnedBalls < totalBalls && spawnTimer >= spawnDelay) {
            float spawnY = 250.f + spawnedBalls * 20.f;
            balls.emplace_back(0.f, spawnY, 0.7f);
            balls.back().setVelocity(300.f, 0.f);
            spawnTimer = 0.f;
            spawnedBalls++;
        }

        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>())
                window.close();

            if (auto* m = event->getIf<Event::MouseButtonPressed>()) {
                clickCounter++;
                text.setString("Broj klikova: " + to_string(clickCounter));

                Vector2f mousePos((float)m->position.x, (float)m->position.y);
                for (auto& ball : balls) {
                    Vector2f delta = mousePos - ball.circle.getPosition();
                    if (delta.x * delta.x + delta.y * delta.y < ball.circle.getRadius() * ball.circle.getRadius()) {
                        float vx = -delta.x * onClickBounce * 0.1f;
                        float vy = -delta.y * onClickBounce * 0.1f;
                        ball.setVelocity(vx, vy);
                        if (clickCounter >= 10) {
                            ball.bounceFactor = 0.3f;
                            text2.setString("Hehe, nakon 10. klika se smanjuje skocnost");
                        }
                    }
                }
            }
        }

        // Physics
        for (auto& ball : balls)
            ball.applyGravity(dt);

        for (auto& ball : balls)
            ball.handleWallCCD();

        for (size_t i = 0; i < balls.size(); i++)
            for (size_t j = i + 1; j < balls.size(); j++)
                balls[i].handleBallCollision(balls[j]);

        for (auto& ball : balls)
            ball.update(dt);

        // Render
        window.clear(Color::Black);
        for (auto& ball : balls)
            window.draw(ball.circle);
        window.draw(text);
        window.draw(text2);
        window.display();
    }

    return 0;
}
