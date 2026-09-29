// Include important libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
// #include <cstdlib>


// Make code easier to type with "using namspace"
// using namespace sf;


// This is where our game starts from
int main() {
  // Create a video mode object
  sf::VideoMode vm({1920, 1080});

  // Create and open a window for the game
  sf::RenderWindow window(vm, "Timber!!",sf::Style::Default);

  // Create a texture to hold a graphic on GPU & load a graphic into the texture
  sf::Texture textureBackground("graphics/background.png");

  // Create a sprite & attach the texture to the sprite
  sf::Sprite spriteBackground(textureBackground);

  // Set the spriteBackground to cover the screen
  spriteBackground.setPosition({0,0});


  // Make a tree sprite
  sf::Texture textureTree("graphics/tree.png");
  sf::Sprite spriteTree(textureTree);
  spriteTree.setPosition({810, 0});


  // Prepare the bee
  sf::Texture textureBee("graphics/bee.png");
  sf::Sprite spriteBee(textureBee);
  spriteBee.setPosition({0, 800});

  // Is the bee currently moving?
  bool beeActive = false;

  // How fast can the bee fly
  float beeSpeed = 0.0f;


  // Make 3 cloud sprites from 1 texture
  sf::Texture textureCloud("graphics/cloud.png");

  // 3 new sprites with the same texture
  sf::Sprite spriteCloud1(textureCloud);
  sf::Sprite spriteCloud2(textureCloud);
  sf::Sprite spriteCloud3(textureCloud);

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
  sf::Clock clock;


  // Track whether the game is running
  bool paused = true;


  // We need to choose a font
  int score{0};

  sf::Font font("fonts/KOMIKAP_.ttf");

  // Draw some text and set the font to out message
  sf::Text messageText(font);
  sf::Text scoreText(font);

  // Assign the actual message
  messageText.setString("Press ENTER to start!");
  scoreText.setString("Score = 0");

  // Make it really big
  messageText.setCharacterSize(75);
  scoreText.setCharacterSize(100);

  // Choose a color
  messageText.setFillColor(sf::Color::White);
  scoreText.setFillColor(sf::Color::White);

  // Position the text
  sf::FloatRect textRect{messageText.getLocalBounds()};
  messageText.setOrigin(textRect.getCenter());
  messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});
  scoreText.setPosition({20 ,0});


  while (window.isOpen()) {
    // Process window events using the SFML3 API
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    // Handle players input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
      window.close();
    }

    // Start the game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
      paused = false;
    }

    // Don't draw after either action closes the window
    if (!window.isOpen()) {
      break;
    }

    // Update the scene and clear everything on the last frame
    window.clear();

    if (!paused) {
      // Measure time
      sf::Time dt = clock.restart();


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
        srand((unsigned int)time(0) * 10);
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

      // Cloud 2
      if (!cloud2Active) {
        // How fast is the cloud
        srand((unsigned int)time(0) * 20);
        cloud2Speed = (rand() % 200);

        // How high is the cloud
        srand((unsigned int)time(0) * 20);
        float height = (rand() % 300) - 150;
        spriteCloud2.setPosition({-200, height});
        cloud2Active = true;
      } else {
        spriteCloud2.setPosition({spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y});

        // Has the cloud reached the right-hand edge of the screen?
        if (spriteCloud2.getPosition().x > 1920) {
          // Set it up ready to be a whole new cloud next frame
          cloud2Active = false;
        }
      }

      // Cloud 3
      if (!cloud3Active) {
        // How fast is the cloud
        srand((unsigned int)time(0) * 30);
        cloud3Speed = (rand() % 200);

        // How high is the cloud
        srand((unsigned int)time(0) * 30);
        float height = (rand() % 450) - 150;
        spriteCloud3.setPosition({-200, height});
        cloud3Active = true;
      } else {
        spriteCloud3.setPosition({spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y});

        // Has the cloud reached the right-hand edge of the screen?
        if (spriteCloud3.getPosition().x > 1920) {
          // Set it up ready to be a whole new cloud next frame
          cloud3Active = false;
        }
      }
      // Update the score text
      std::stringstream ss;
      ss << "Score = " << score;
      scoreText.setString(ss.str());
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
    // Draw the score
    window.draw(scoreText);
    if (paused) {
      // Draw our message
      window.draw(messageText);
    }
    // Show everything we just drew
    window.display();
  }

  return 0;
}
