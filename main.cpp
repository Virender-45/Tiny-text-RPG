#include <bits/stdc++.h>
using namespace std;

// Utility random
int rand_range(int a, int b){ return a + rand() % (b - a + 1); }

struct Item {
    string name;
    int heal;
    Item(string n="", int h=0):name(n),heal(h){}
};

struct Player {
    string name;
    string pclass;
    int level;
    int xp;
    int max_hp;
    int hp;
    int atk;
    int def;
    int gold;
    vector<Item> inventory;

    Player():level(1),xp(0),max_hp(20),hp(20),atk(4),def(1),gold(20){}

    void gain_xp(int amount){
        xp += amount;
        while(xp >= level*10){
            xp -= level*10;
            level_up();
        }
    }
    void level_up(){
        level++;
        int hp_gain = rand_range(4,8);
        max_hp += hp_gain;
        hp = max_hp;
        atk += 2;
        def += 1;
        std::cout << "\n*** You reached level "<< level <<"! (+"<< hp_gain <<" HP, +2 ATK, +1 DEF) ***\n";
    }
    void show_stats(){
        std::cout << "\n-- "<< name << " the " << pclass << " --\n";
        std::cout << "Level: "<< level << "   XP: " << xp << "/" << level*10 << "\n";
        std::cout << "HP: "<< hp << "/"<< max_hp << "   ATK: "<< atk << "   DEF: "<< def << "\n";
        std::cout << "Gold: "<< gold << "\n";
    }
    void add_item(const Item &it){ inventory.push_back(it); }
    bool use_potion(){
        for(size_t i=0;i<inventory.size();++i){
            if(inventory[i].heal>0){
                int heal = inventory[i].heal;
                hp = min(max_hp, hp + heal);
                std::cout << "You used "<< inventory[i].name <<" and recovered "<< heal <<" HP.\n";
                inventory.erase(inventory.begin()+i);
                return true;
            }
        }
        std::cout << "No potions available!\n";
        return false;
    }
};

struct Enemy {
    string name;
    int hp;
    int atk;
    int def;
    int xp_reward;
    int gold_reward;
};

Enemy make_enemy(int player_level){
    // scale enemy with player level
    int type = rand_range(1,3);
    Enemy e;
    if(type==1){
        e.name = "Goblin";
        e.hp = rand_range(8,12) + player_level*2;
        e.atk = rand_range(2,4) + player_level/2;
        e.def = rand_range(0,1) + player_level/3;
        e.xp_reward = 5 + player_level*2;
        e.gold_reward = rand_range(3,8) + player_level;
    } else if(type==2){
        e.name = "Wolf";
        e.hp = rand_range(10,14) + player_level*2;
        e.atk = rand_range(3,6) + player_level/2;
        e.def = rand_range(0,2) + player_level/3;
        e.xp_reward = 6 + player_level*2;
        e.gold_reward = rand_range(4,10) + player_level;
    } else {
        e.name = "Bandit";
        e.hp = rand_range(12,16) + player_level*2;
        e.atk = rand_range(4,7) + player_level/2;
        e.def = rand_range(1,2) + player_level/3;
        e.xp_reward = 8 + player_level*3;
        e.gold_reward = rand_range(6,12) + player_level;
    }
    return e;
}

void press_enter(){
    std::cout << "\n(Press Enter to continue...)";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void combat(Player &pl){
    Enemy e = make_enemy(pl.level);
    std::cout << "\nYou encounter a "<< e.name << "!\n";
    while(e.hp>0 && pl.hp>0){
        std::cout << "\nEnemy: "<< e.name << "  HP:"<< e.hp <<"\n";
        pl.show_stats();
        std::cout << "\nChoose action: 1) Attack  2) Defend  3) Use Potion  4) Flee\n> ";
        int choice; if(!(cin>>choice)){ cin.clear(); cin.ignore(1000,'\n'); choice=0; }
        cin.ignore(1000,'\n');
        if(choice==1){
            int damage = max(1, pl.atk - e.def + rand_range(0,3));
            e.hp -= damage;
            std::cout << "You strike the "<< e.name <<" for "<< damage <<" damage.\n";
        } else if(choice==2){
            std::cout << "You brace for the enemy's attack (defense up).\n";
        } else if(choice==3){
            pl.use_potion();
        } else if(choice==4){
            int chance = rand_range(1,100);
            if(chance <= 50 + pl.level*2){ std::cout << "You successfully fled!\n"; return; }
            else { std::cout << "You failed to escape!\n"; }
        } else { std::cout << "Invalid choice. You lose your turn.\n"; }

        // Enemy turn (unless dead)
        if(e.hp>0){
            int enemy_atk = e.atk + rand_range(0,2);
            int defender = e.def;
            bool player_defending = (choice==2);
            int effective_def = pl.def + (player_defending?3:0);
            int damage = max(0, enemy_atk - effective_def + rand_range(0,2));
            if(damage==0) std::cout << "The "<< e.name <<"'s attack couldn't penetrate your defense.\n";
            else {
                pl.hp -= damage;
                std::cout << "The "<< e.name <<" hits you for "<< damage <<" damage.\n";
            }
        }
    }
    if(pl.hp <= 0){
        std::cout << "\nYou were defeated by the "<< e.name <<"... You lose half your gold and wake up at full health.\n";
        pl.gold = pl.gold/2;
        pl.hp = pl.max_hp;
    } else {
        std::cout << "\nYou defeated the "<< e.name <<"!\n";
        std::cout << "You gain "<< e.xp_reward <<" XP and "<< e.gold_reward <<" gold.\n";
        pl.gain_xp(e.xp_reward);
        pl.gold += e.gold_reward;
        // chance to drop a potion
        if(rand_range(1,100) <= 30){
            pl.add_item(Item("Small Potion", rand_range(6,12)));
            std::cout << "The "<< e.name <<" dropped a Small Potion!\n";
        }
    }
    press_enter();
}

void show_inventory(const Player &pl){
    std::cout << "\n-- Inventory --\n";
    if(pl.inventory.empty()) std::cout << "(empty)\n";
    else{
        for(size_t i=0;i<pl.inventory.size();++i){
            std::cout << i+1<<") "<< pl.inventory[i].name <<" (Heals "<< pl.inventory[i].heal <<" HP)\n";
        }
    }
    std::cout << "\nGold: "<< pl.gold <<"\n";
}

void shop(Player &pl){
    std::cout << "\n-- Shop --\n1) Small Potion (10 gold) - heals 10-14 HP\n2) Medium Potion (25 gold) - heals 20-30 HP\n3) Exit shop";

    while(true){
        std::cout << "\nChoose item to buy (1-3): ";
        int c; if(!(cin>>c)){ cin.clear(); cin.ignore(1000,'\n'); c=3; }
        cin.ignore(1000,'\n');
        if(c==1){ if(pl.gold>=10){ pl.gold-=10; pl.add_item(Item("Small Potion", rand_range(10,14))); std::cout<<"Purchased Small Potion.\n";} else std::cout<<"Not enough gold.\n"; }
        else if(c==2){ if(pl.gold>=25){ pl.gold-=25; pl.add_item(Item("Medium Potion", rand_range(20,30))); std::cout<<"Purchased Medium Potion.\n";} else std::cout<<"Not enough gold.\n"; }
        else break;
    }
}

void save_game(const Player &pl){
    ofstream f("savegame.txt");
    if(!f) { std::cout<<"Failed to open save file.\n"; return; }
    f<<pl.name<<"\n"<<pl.pclass<<"\n"<<pl.level<<" "<<pl.xp<<" "<<pl.max_hp<<" "<<pl.hp<<" "<<pl.atk<<" "<<pl.def<<" "<<pl.gold<<"\n";
    f<<pl.inventory.size() << "\n";
    for(auto &it: pl.inventory) f<< it.name <<"|"<< it.heal <<"\n";
    f.close();
    std::cout << "Game saved.\n";
}

bool load_game(Player &pl){
    ifstream f("savegame.txt");
    if(!f) { std::cout<<"No save file found.\n"; return false; }
    getline(f, pl.name);
    getline(f, pl.pclass);
    f >> pl.level >> pl.xp >> pl.max_hp >> pl.hp >> pl.atk >> pl.def >> pl.gold;
    int n; f >> n; f.ignore(1000,'\n');
    pl.inventory.clear();
    for(int i=0;i<n;i++){
        string line; getline(f,line);
        size_t pos = line.find('|');
        if(pos!=string::npos){
            string iname = line.substr(0,pos);
            int iheal = stoi(line.substr(pos+1));
            pl.inventory.push_back(Item(iname,iheal));
        }
    }
    std::cout << "Game loaded.\n";
    return true;
}

int main(){
    srand((unsigned)time(NULL));
    Player player;

    std::cout << "*** Welcome to Tiny Text RPG ***\n";
    std::cout << "1) New Game\n2) Load Game\nChoose: ";
    int start_choice; if(!(cin>>start_choice)){ cin.clear(); cin.ignore(1000,'\n'); start_choice=1; }
    cin.ignore(1000,'\n');
    if(start_choice==2){ if(!load_game(player)) start_choice=1; }

    if(start_choice==1){
        std::cout << "Enter your name: "; getline(cin, player.name);
        std::cout << "Choose class: 1) Warrior 2) Mage 3) Rogue\n> ";
        int cls; if(!(cin>>cls)){ cls=1; }
        cin.ignore(1000,'\n');
        if(cls==1){ player.pclass="Warrior"; player.max_hp = 30; player.hp=30; player.atk=6; player.def=2; }
        else if(cls==2){ player.pclass="Mage"; player.max_hp = 22; player.hp=22; player.atk=8; player.def=1; }
        else { player.pclass="Rogue"; player.max_hp = 24; player.hp=24; player.atk=7; player.def=1; }
        // starter item
        player.inventory.push_back(Item("Small Potion", 12));
        std::cout << "\nWelcome, "<< player.name <<" the "<< player.pclass <<"!\n";
        press_enter();
    }

    // main loop
    while(true){
        std::cout << "\n=== Town Menu ===\n1) Go on Adventure (fight)\n2) Rest (restore HP for 10 gold)\n3) Inventory\n4) Shop\n5) Save Game\n6) Exit\nChoose: ";
        int option; if(!(cin>>option)){ cin.clear(); cin.ignore(1000,'\n'); option=6; }
        cin.ignore(1000,'\n');
        if(option==1){ combat(player); }
        else if(option==2){ if(player.gold>=10){ player.gold-=10; player.hp = player.max_hp; std::cout<<"You rested and restored your HP.\n";} else std::cout<<"Not enough gold to rest.\n"; }
        else if(option==3){ show_inventory(player); std::cout<<"\n1) Use Potion  2) Back\nChoose: "; int c; if(!(cin>>c)){ c=2; } cin.ignore(1000,'\n'); if(c==1) player.use_potion(); }
        else if(option==4){ shop(player); }
        else if(option==5){ save_game(player); }
        else if(option==6){ std::cout << "Goodbye adventurer!\n"; break; }
        else { std::cout<<"Invalid option.\n"; }
    }
    return 0;
}
