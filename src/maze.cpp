#include "maze.h"  

// Maze constructor with width and height
Maze::Maze(int width, int height) {
    srand(static_cast<unsigned int>(time(0)));
    generateMaze(width, height);
}

// Checks if position is vaild  
bool Maze::isValidPosition(std::pair<int, int> position) const {
    return (position.first >= 0 && position.first < WIDTH) &&
        (position.second >= 0 && position.second < HEIGHT);
}


// Picks a random direction to walk in  
Direction Maze::pickRandomDirection(std::vector<Direction>& directions) {
    return directions[rand() % directions.size()];
}

// Gets the opposite direction  
Direction Maze::getOppositeDirection(Direction direction) const {  
	Direction opposite = Direction::NORTH;

    switch (direction) {
    case Direction::NORTH:
        opposite = Direction::SOUTH;
		break;
    case Direction::SOUTH:
        opposite = Direction::NORTH;
        break;
    case Direction::EAST:
        opposite = Direction::WEST;
        break;
    case Direction::WEST:
        opposite = Direction::EAST;
        break;
    default: 
        break;
    }

	return opposite;
}  

// Links nodes in the maze  
void Maze::linkNodes(std::pair<int, int> start, std::pair<int, int> end) {  
   // Get the nodes  
   std::unique_ptr<MazeNode>& startNode = mazeMap[start];  
   std::unique_ptr<MazeNode>& endNode = mazeMap[end];  

   if (startNode && endNode) {
       // Determine the direction based on position differences
       Direction direction;
       if (start.first == end.first) {
           direction = (start.second < end.second) ? Direction::EAST : Direction::WEST;
       }
       else {
           direction = (start.first < end.first) ? Direction::SOUTH : Direction::NORTH;
       }

       // Link the nodes
       startNode->addNeighbor(endNode.get(), direction);
       endNode->addNeighbor(startNode.get(), getOppositeDirection(direction));
   }
}  

// Erase any loop that occurs in the walk
std::vector<std::pair<int, int>> Maze::eraseLoop(std::vector<std::pair<int, int>> path, std::pair<int, int> current) {
    auto startOfLoop = std::find(path.begin(), path.end(), current);
    if (startOfLoop != path.end()) {
        path.erase(startOfLoop + 1, path.end()); // Preserve 'current' in the path
    }
    return path;
}

 
// Next step in the walk  
std::pair<int, int> Maze::nextStep(std::pair<int, int> current) {
    std::vector<Direction> directions = { Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST };
    std::pair<int, int> next = current;

    // Keep picking directions until a valid position is found or no directions remain
    while (directions.size() > 0) {
        // Pick a random direction
        Direction direction = pickRandomDirection(directions);

        switch (direction) {
        case Direction::NORTH:
            if (current.second - 1 > OUT_OF_BOUNDS) {
                next = std::make_pair(current.first, current.second - 1);
            }
            break;
        case Direction::SOUTH:
            if (current.second + 1 < HEIGHT) {
                next = std::make_pair(current.first, current.second + 1);
            }
            break;
        case Direction::EAST:
            if (current.first + 1 < WIDTH) {
                next = std::make_pair(current.first + 1, current.second);
            }
            break;
        case Direction::WEST:
            if (current.first - 1 > OUT_OF_BOUNDS) {
                next = std::make_pair(current.first - 1, current.second);
            }
            break;
        }

        // If the next position is valid, return it
        if (isValidPosition(next)) {
            return next;
        }

        // Remove the chosen direction from the list since it led to an invalid move
        directions.erase(std::remove(directions.begin(), directions.end(), direction), directions.end());
    }

    // If no valid moves are found, return the current position (i.e., no movement)
    return next;
}


// Start random walk  
std::vector<std::pair<int, int>> Maze::randomWalk(std::pair<int, int> start) {
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = start;

    // Continue walking until a node in the maze is encountered
    while (visited.find(current) == visited.end()) {
        path.push_back(current); 

        std::pair<int, int> next = nextStep(current);

        // If no valid movement is possible (next == current), break the loop
        if (next == current) {
            break;
        }

        current = next;
        path = eraseLoop(path, current);
    }

    return path;
}


// Generate maze  
void Maze::generateMaze(int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    mazeMap.clear();
    visited.clear();

    // Set to hold all available positions not yet in the maze
    std::set<std::pair<int, int>> availablePositions;

    // Create nodes for each position in the maze
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            mazeMap[std::make_pair(i, j)] = std::make_unique<MazeNode>();
        }
    }

    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            // Link east if not on the right edge
            if (j + 1 < HEIGHT) {
                linkNodes(std::make_pair(i, j), std::make_pair(i, j + 1));
            }

            // Link south if not on the bottom edge
            if (i + 1 < WIDTH) {
                linkNodes(std::make_pair(i, j), std::make_pair(i + 1, j));
            }
        }
    }
}

//Pick a random start and end position for the maze
void Maze::chooseStartAndEnd() {
	start = std::make_pair(0, rand() % WIDTH);
	end = std::make_pair(HEIGHT - 1, rand() % WIDTH);
}


// Print the maze to the console
void Maze::printMaze() {
    screenBuffer.clearScreen();

    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            std::pair<int, int> position = std::make_pair(col, row);
			screenBuffer.writeToScreen(col * pathWidth + 1, row * pathWidth + 1, L" ", ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BLUE);

			// Add in paths for each node
            if (mazeMap.at(position)->getNeighbor(Direction::EAST) != nullptr){
                screenBuffer.writeToScreen(col * pathWidth + 2, row * pathWidth + 1, L" ", ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BLUE);
            }
            else if (mazeMap.at(position)->getNeighbor(Direction::SOUTH) != nullptr) {
                screenBuffer.writeToScreen(col * pathWidth + 1, row * pathWidth + 2, L" ", ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BLUE);
            }

			// Add player position and start/end positions
			if (position == playerPosition) {
				screenBuffer.writeToScreen(col * pathWidth + 1, row * pathWidth + 1, L" ", ScreenBuffer::BLACK, ScreenBuffer::GREEN);
			}
			if (position == start) {
				screenBuffer.writeToScreen(col * pathWidth + 1, row * pathWidth + 1, L" ", ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::RED);
			}
			else if (position == end) {
				screenBuffer.writeToScreen(col * pathWidth + 1, row * pathWidth + 1, L" ", ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::RED);
			}
        }
    }
}

// Run the maze game
int Maze::run() {
	// Set the player position to the start of the maze
	playerPosition = start;

	// Print the maze
	chooseStartAndEnd();
	std::pair<int, int> currentPosition;

	printMaze();
    screenBuffer.setActive();

	//Sleep(100000);

	// Loop until the player reaches the end of the maze
	while (playerPosition != end) {
		// Get the player input
		int input = _getch();
		currentPosition = playerPosition;

		// Move the player based on the input
		switch (input) {
		case VK_UP:
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::NORTH) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first, playerPosition.second - 1);
			}
			break;
		case VK_DOWN:
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::SOUTH) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first, playerPosition.second + 1);
			}
			break;
		case VK_LEFT:
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::WEST) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first - 1, playerPosition.second);
			}
			break;
		case VK_RIGHT:
			if (mazeMap.at(playerPosition)->getNeighbor(Direction::EAST) != nullptr) {
				playerPosition = std::make_pair(playerPosition.first + 1, playerPosition.second);
			}
			break;
		default:
			break;
		}

		screenBuffer.writeToScreen(currentPosition.second * pathWidth + 1, currentPosition.first * pathWidth + 1, L" ", ScreenBuffer::FOREGROUND_NORMAL, ScreenBuffer::BLUE);
		screenBuffer.writeToScreen(playerPosition.second * pathWidth + 1, playerPosition.first * pathWidth + 1, L"*", ScreenBuffer::BLACK, ScreenBuffer::GREEN);
		currentPosition = playerPosition;
	}

	return 0;
}