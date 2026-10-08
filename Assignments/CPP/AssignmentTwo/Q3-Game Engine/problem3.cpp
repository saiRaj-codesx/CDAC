#include <iostream>
#include <cstdlib> 

using namespace std;


int level = 1; 

namespace Engine {
 namespace Audio {
 void playSound(string name) {
 cout << "Playing: " << name << endl;
  }
 }
}

int main() {
    
    int level = 10; 
    
    cout << "Global level (difficulty): " << ::level << endl;
    cout << "Local level (player): " << level << endl;
    
    Engine::Audio::playSound("sword_clash");
    cout << endl;
  
    int R, C;
    cout << "Enter rows and columns: ";
    cin >> R >> C;

    int** map = new int*[R];
    for (int i = 0; i < R; i++) {
        map[i] = new int[C];
    }

  
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            map[i][j] = rand() % 5; 
        }
    }

    
    cout << "\n   GAME MAP (" << R << " x " << C << ")  " << endl;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n"; 
    }
    
    cout << "\nLegend: 0=Grass  1=Water  2=Mountain  3=Forest  4=Dungeon\n" << endl;

    int grass = 0;
    int water = 0;
    int mountain = 0;
    int forest = 0;
    int dungeon = 0;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] == 0) grass++;
            else if (map[i][j] == 1) water++;
            else if (map[i][j] == 2) mountain++;
            else if (map[i][j] == 3) forest++;
            else if (map[i][j] == 4) dungeon++;
        }
    }

    cout << "Tile Count:" << endl;
    cout << "  Grass    : " << grass << endl;
    cout << "  Water    : " << water << endl;
    cout << "  Mountain : " << mountain << endl;
    cout << "  Forest   : " << forest << endl;
    cout << "  Dungeon  : " << dungeon << endl;


    for (int i = 0; i < R; i++) {
        delete[] map[i]; 
    }
    delete[] map; 
    return 0;
}
