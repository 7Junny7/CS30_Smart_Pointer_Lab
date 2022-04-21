#include <memory>
#include <iostream>
#include <string>
#include <optional>
using namespace std;

struct FootBallPlayer {
	string name;
	int num;
};

struct Node {
    FootBallPlayer player;
    shared_ptr<Node> next;
    Node(FootBallPlayer p) : player(p){}
};

class FootBallRoster {
private:
    shared_ptr<Node> head;
    weak_ptr<Node> favorite;
public:
    FootBallRoster() : head(nullptr){}
    ~FootBallRoster(){
//        Node *temp;
//        while (head != nullptr){
//            temp = head;
//            head = head->next;
//            delete temp;
//        }
    }
	 // Adds a FootBallPlayer to the roster.
	void addPlayer(FootBallPlayer player);

	 // deletes the first FootBallPlayer that matches name
	bool deletePlayer(string name);

	 // Uses a weak_ptr to return true if the
	bool setFavorite(string name);

	 // Returns an optional parameter if there is a favorite player
	std::optional<FootBallPlayer> getFavorite() const;

	 // Prints the list of FootBallPlayers on the roster
	void printPlayers() const;
};

 // prints out the name of the favorite player or a message
 // stating there is no favorite player.
void favoritePlayer(const FootBallRoster& roster);

int main() {

    FootBallPlayer fb1{ "Matthew Stafford", 9 };
    FootBallPlayer fb2{ "Aaron Donald", 99 };
    FootBallPlayer fb3{ "Jalen Ramsey", 5 };

    FootBallRoster roster;

    roster.addPlayer(fb1);
    roster.addPlayer(fb2);
    roster.addPlayer(fb3);

    roster.printPlayers();
    roster.setFavorite("Aaron Donald");

    favoritePlayer(roster);

    roster.deletePlayer("Aaron Donald");
    favoritePlayer(roster);
}

void FootBallRoster::addPlayer(FootBallPlayer player) {
    // Adds a FootBallPlayer to the roster.

    //for raw pointer
//    Node *temp = new Node{player, nullptr};
//    if (this->head == nullptr){
//        this->head = temp;
//    }else{
//        Node *iterator = head;
//        while (iterator->next != nullptr){
//            iterator = iterator->next;
//        }
//        iterator->next = temp;
//    }


    shared_ptr<Node> temp = make_shared<Node>(player);
    if(this->head == nullptr){
        this->head = temp;
    }else{
        //case 1 insert to rear
//        shared_ptr<Node> iterator = head;
//        while(iterator->next != nullptr){
//            iterator = iterator->next;
//        }
//        iterator->next = temp;

        //case 2 insert to front
        shared_ptr<Node> iterator = head;
        temp->next = iterator;
        head = temp;
    }
}
bool FootBallRoster::deletePlayer(string name) {
    // deletes the first FootBallPlayer that matches name

    //for raw pointer
//    Node *iterator = head;
//    while (iterator != nullptr){
//        if(iterator->player.name == name){
//            break;
//        }
//        iterator = iterator->next;
//    }
//    if (iterator == nullptr){
//        return false;
//    }else{
//        if (iterator->next == nullptr){
//            delete
//        }
//    }

    shared_ptr<Node> iterator = head;
    shared_ptr<Node> iterator_before;
    while (iterator != nullptr){
        if (iterator->player.name == name){
            break;
        }
        iterator_before = iterator;
        iterator = iterator->next;
    }
    if (iterator == nullptr){
        return false;
    }else{
        if (iterator->next == nullptr){
            iterator.reset();
            delete iterator.get();
            return true;
        }else{
            iterator_before->next = iterator->next;
            iterator.reset();
            delete iterator.get();
            return true;
        }
    }

}
bool FootBallRoster::setFavorite(string name) {
    // Uses a weak_ptr to return true if the
    shared_ptr<Node> iterator = head;
    while (iterator != nullptr){
        if (iterator->player.name == name){
            break;
        }
        iterator = iterator->next;
    }
    if (iterator == nullptr){
        return false;
    }else{
        if (iterator->player.name == name){
            this->favorite = iterator;
            return true;
        }
    }
}
std::optional<FootBallPlayer> FootBallRoster::getFavorite() const {
    // Returns an optional parameter if there is a favorite player
    if (this->favorite.lock() != nullptr){
        return this->favorite.lock()->player;
    }
    return {};
}
void FootBallRoster::printPlayers() const {
    // Prints the list of FootBallPlayers on the roster

    //for raw pointer
//    Node *iterator = head;
//    while (iterator != nullptr){
//        cout<<iterator->player.name<<" #"<<iterator->player.num<<endl;
//        iterator = iterator->next;
//    }

    shared_ptr<Node> iterator = head;
    while(iterator != nullptr){
        cout<<iterator->player.name<<" #"<<iterator->player.num<<endl;
        iterator = iterator->next;
    }
}

void favoritePlayer(const FootBallRoster& roster){
    // prints out the name of the favorite player or a message
    // stating there is no favorite player.

    //use weak pointer
    if (roster.getFavorite().has_value()){
        cout<<"Your favorite player is: "<<roster.getFavorite().value().name<<endl;
    }else{
        cout<<"You don't have a favorite player"<<endl;
    }
}
