#include <iostream>
#include <string>
#include <memory> 

using namespace std;

// --- Part A: Texture Class ---
class Texture {
private:
    string name;
    int width;
    int height;

public:
    Texture(string n, int w, int h) {
        name = n;
        width = w;
        height = h;
        cout << "[Texture Loaded]" << endl;
    }
    
    ~Texture() {
        cout << "[Texture Released]" << endl;
    }
    
    void display() const {
        cout << "Texture: " << name << " (" << width << "x" << height << ")" << endl;
    }
};

// --- Part B: Shader Class ---
class Shader {
private:
    string name;
    string type;

public:
    Shader(string n, string t) {
        name = n;
        type = t;
        cout << "[Shader Compiled]" << endl;
    }
    
    ~Shader() {
        cout << "[Shader Destroyed]" << endl;
    }
};

// --- Part C: AudioClip Class ---
class AudioClip {
private:
    string name;
    double duration;

public:
    AudioClip(string n, double d) {
        name = n;
        duration = d;
    }
    
    string getName() const {
        return name;
    }
};

int main() {
    // --- Part A : unique_ptr ---
    cout << "--- Part A: unique_ptr ---" << endl;
    auto tex1 = make_unique<Texture>("player_sprite", 512, 512);
    tex1->display();
    
   
    
    unique_ptr<Texture> tex2 = move(tex1);
    cout << "tex1 is null: " << (tex1 == nullptr ? "YES" : "NO") << endl;
    cout << endl;

    // --- Part B : shared_ptr ---
    cout << "--- Part B: shared_ptr ---" << endl;
    auto shader = make_shared<Shader>("main_vert", "vertex");
    cout << "Ref count: " << shader.use_count() << endl; // Should be 1
    {
        auto rendererRef = shader;
        cout << "Ref count: " << shader.use_count() << endl; // Should be 2
        
        auto editorRef = shader;
        cout << "Ref count: " << shader.use_count() << endl; // Should be 3
    }
    cout << "Ref count: " << shader.use_count() << endl; // Should drop back to 1
    cout << endl;

    // --- Part C : weak_ptr ---
    cout << "--- Part C: weak_ptr ---" << endl;
    auto audio = make_shared<AudioClip>("explosion", 3.5);
    weak_ptr<AudioClip> observer = audio;
    
    if (auto clip = observer.lock()) {
        cout << "Clip alive: " << clip->getName() << endl;
    }
    
    audio.reset(); 
    
    if (observer.expired()) {
        cout << "Clip already unloaded." << endl;
    }
    
    return 0;
}
