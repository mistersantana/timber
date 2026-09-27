// Include important libraries here
#include <SFML/Graphics.hpp>
#include <cstdlib>


// Make code easier to type with "using namspace"
using namespace sf;


// This is where our game starts from
int main() {
  // Create a video mode object
  VideoMode vm({1920, 1080});

  // Create and open a window for the game
  RenderWindow window(vm, "Timber!!",Style::Close);

  // Create a texture to hold a graphic on GPU & load a graphic into the texture
  Texture textureBackground("graphics/background.png");

  // Create a sprite & attach the texture to the sprite
  Sprite spriteBackground(textureBackground);

  // Set the spriteBackground to cover the screen
  spriteBackground.setPosition({0,0});


  // Make a tree sprite
  Texture textureTree("graphics/tree.png");
  Sprite spriteTree(textureTree);
  spriteTree.setPosition({810, 0});


  // Prepare the bee
  Texture textureBee("graphics/bee.png");
  Sprite spriteBee(textureBee);
  spriteBee.setPosition({0, 800});

  // Is the bee currently moving?
  bool beeActive = false;

  // How fast can the bee fly
  float beeSpeed = 0.0f;


  // Make 3 cloud sprites from 1 texture
  Texture textureCloud("graphics/cloud.png");

  // 3 new sprites with the same texture
  Sprite spriteCloud1(textureCloud);
  Sprite spriteCloud2(textureCloud);
  Sprite spriteCloud3(textureCloud);

  // Position the clouds on the left of the screen at different heights
  spriteCloud1.setPosition({0, 0});
  spriteCloud2.setPosition({0, 250});
  spriteCloud3.setPosition({0, 500});

  // Are the clouds currently on screen?
  bool cloud1Active = false;
  bool cloud2Active = false;
  bool cloud3Active = false;

  // How fast is each cloud?
  float cloud1Speed = 0.0f;
  float cloud2Speed = 0.0f;
  float cloud3Speed = 0.0f;

  // Variables to control time
  Clock clock;


  while (window.isOpen()) {
    // Process window events using the SFML3 API
    while (const auto event = window.pollEvent()) {
      if (event->is<Event::Closed>()) {
        window.close();
      }
    }

    // Handle players input
    if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
      window.close();
    }

    // Don't draw after either action closes the window
    if (!window.isOpen()) {
      break;
    }

    // Update the scene and clear everything on the last frame
    window.clear();

    // Measure time
    Time dt = clock.restart();


    // Setup the bee
    if (!beeActive) {
      // How fast is the bee
      srand((unsigned int)time(0));
      beeSpeed = (rand() % 200) + 200;

      // How high is the bee
      srand((unsigned int)time(0) * 10);
      float height = (rand() % 500) + 500;
      spriteBee.setPosition({2000, height});
      beeActive = true;
    } else {
      // Move the bee
      spriteBee.setPosition({spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y});

      // Has the bee reached the left-hand edge of the screen?
      if (spriteBee.getPosition().x < -100) {
        // Set it up ready to be a whole new bee next frame
        beeActive = false;
      }
    }


    // Manage the clouds
    // Cloud 1
    if (!cloud1Active) {
      // How fast is the cloud
      srand((unsigned int)time(0));
      cloud1Speed = (rand() % 200);

      // How high is the cloud
      srand((unsigned int)time(0) * 10);
      float height = (rand() % 150);
      spriteCloud1.setPosition({-200, height});
      cloud1Active = true;
    } else {
      spriteCloud1.setPosition({spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y});

      // Has the cloud reached the right-hand edge of the screen?
      if (spriteCloud1.getPosition().x > 1920) {
        // Set it up ready to be a whole new cloud next frame
        cloud1Active = false;
      }
    }


    // Draw our game scene here
    window.draw(spriteBackground);
    // Draw the clouds
    window.draw(spriteCloud1);
    window.draw(spriteCloud2);
    window.draw(spriteCloud3);
    // Draw the tree
    window.draw(spriteTree);
    // Draw the insect
    window.draw(spriteBee);
    // Show everything we just drew
    window.display();
  }

  return 0;
}
