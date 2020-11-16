### Tanks network (client-server) game

The game is an enhanced multiplayer version of [this](https://github.com/emelyantsev/my-tank-battle-game) game.


It contains a multithreaded game server which has some interesting features:
- handles client connect-disconnect and waiting state,
- game session management for two clients,

Some interesting algotrithms for collision detection:
- intersection of rotated rectangles [ref](https://stackoverflow.com/questions/10962379/how-to-check-intersection-between-2-rotated-rectangles),
- intersection of point and rotated rectangle.

Also there is a dockerfile to run server in docker.

#### **Gameplay example**
![Gameplay](https://github.com/emelyantsev/my-tank-battle-game-online/blob/main/images/record.gif)

