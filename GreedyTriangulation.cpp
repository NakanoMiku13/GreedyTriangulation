#include<bits/stdc++.h>
using namespace std;
float maxHeight, minHeight, minWidth, maxWidth;
template<typename datatype, typename datatype2>
class Pair{
    public:
        datatype x;
        datatype2 y;
        Pair(datatype x, datatype2 y){
            this->x = x;
            this->y = y;
        }
        Pair(){
            this->x = (datatype)NULL;
            this->y = (datatype)NULL;
        }
        auto operator==(const auto& other){
            return (x == other.x) && (y == other.y);
        }
        auto operator!=(const auto& other){
            return (this->x != other.x && this->y != other.y);
        }
        auto operator!=(nullptr_t){
            return this != nullptr;
        }
        auto operator==(nullptr_t){
            return this == nullptr;
        }
        auto operator<(const auto& other){
            return this->x < other.x && this->y < other.y;
        }
        auto operator>(const auto& other){
            return this->x > other.x && this->y > other.y;
        }
        template<typename data,typename data2> friend ostream& operator<<(ostream& out,const Pair<data,data2>& self);
        ~Pair(){
            
        }
};
template<typename datatype1,typename datatype2,typename datatype3,typename datatype4> auto operator<(const Pair<datatype1,datatype2>& first, const Pair<datatype3,datatype4>& second){
    return (first.x < second.x) && (first.y < second.y);
}
template<typename datatype1,typename datatype2,typename datatype3,typename datatype4> auto operator==(const Pair<datatype1,datatype2>& first, const Pair<datatype3,datatype4>& second){
    return (first.x == second.x) && (first.y == second.y);
}
template<typename data,typename data2> ostream& operator<<(ostream& out, const Pair<data,data2>& self){
    out << "X: "<<self.x << " Y: "<<self.y;
    return out;
}
class Connection{
    private:
        Pair<float,float> _first, _last;
        bool _connected;
        vector<Pair<float,float>> _coordinates;
    public:
        Connection(auto first = Pair<float,float>(), auto last = Pair<float,float>()): _first{first},_last{last}{
            _coordinates = vector<Pair<float,float>>();
            _connected = false;
        }
        Connection(){
            _first = Pair<float,float>();
            _last = Pair<float,float>();
            _connected = false;
            _coordinates = vector<Pair<float,float>>();
        }
        auto setCoordinates(auto coordinates){
            this->_coordinates = coordinates;
        }
        auto setFirst(auto first){
            this->_first = first;
        }
        auto setLast(auto last){
            this->_last = last;
        }
        auto getCoordinates(){
            return this->_coordinates;
        }
        auto getFirst(){
            return this->_first;
        }
        auto getLast(){
            return this->_last;
        }
        auto isConnected(){
            return this->_connected;
        }
        auto setLine(auto begin, auto end){
            const float distanceBetweenPoints = 1;
            try{
                if(distanceBetweenPoints == 0) throw 1;
                if(_connected) throw 3;
                float spaceX = (end.x - begin.x) * (distanceBetweenPoints) / 100, spaceY = (end.y - begin.y) * (distanceBetweenPoints) / 100;
                float begin_countX = begin.x + spaceX, begin_countY = begin.y + spaceY;
                vector<Pair<float,float>> coordinates;
                for(int i = 1, k = 1 ; i <= 99 ; i ++, begin_countX += spaceX, begin_countY += spaceY) {
                    coordinates.push_back(Pair<float,float>(begin_countX,begin_countY));
                }
                this->_coordinates = coordinates;
                this->_connected = true;
                this->_first = begin;
                this->_last = end;
            }catch(const int exception){
                cout<<"Error "<<exception<<endl;
            }
        }
        friend ostream& operator<<(ostream& out,Connection& self);
        ~Connection(){

        }
};
ostream& operator<<(ostream& out,Connection& self){
    out << "First: " << self.getFirst() << " Second: " << self.getLast() << endl << "Line: \n";
    for(auto i : self.getCoordinates()) out << i << endl;
    return out;
}
template<typename value> using pointer = value*;
template<typename key, typename value> class Node{
    public:
        key first;
        value second;
        pointer<Node> right,left;
        Node(key first = NULL, value second = NULL): first{first},second{second},right{nullptr},left{nullptr}{}
        Node(pair<key,value> newValue){
            first = newValue.first;
            second = newValue.second;
            right = left = nullptr;
        }
    ~Node(){

    }
};
template<typename key, typename value> class MyMap{
    private:
        pointer<Node<key,value>> _root;
        size_t _size;
        auto _setNode(auto& root,const auto newValue)->void{
            if(root->first < newValue->first){
                if(root->left == nullptr) root->left = newValue;
                else _setNode(root->left, newValue);
            }else{
                if(root->right == nullptr) root->right = newValue;
                else _setNode(root->right, newValue);
            }
        }
        auto _findNode(auto& root,key val){
            if(root == nullptr) return pointer<Node<key,value>>();
            if(root->first == val) return root;
            else{
                return (root->first < val) ? _findNode(root->left,val) : _findNode(root->right,val);
            }
        }
    public:
        MyMap(): _size{0},_root{nullptr}{}
        MyMap(initializer_list<MyMap<key,value>> list){
            for(auto i : list) this->Add(i);
        }
        auto empty(){
            return (_size == 0 or not _root) ? true : false;
        }
        auto Add(pair<key,value> newValue){
            auto newNode = new Node<key,value>(newValue);
            if(empty()) _root = newNode;
            else{
                _setNode(_root,newNode);
            }
            _size++;
        }
        auto exist(key keyVal){
            return (_findNode(_root,keyVal) != nullptr) ? true : false;
        }
        auto begin(){
            return *_root;
        }
        ~MyMap(){}
};
auto distanceBetweenTwoPoints(auto vector1, auto vector2)->double{
    double x1 = vector1.x, x2 = vector2.x, y1 = vector1.y, y2 = vector2.y;
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}
auto possibleConnections(auto coordinates,auto coordinatesList, vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> possibleConnectionsList = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>())->vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>{
    if(coordinatesList.empty()) {return possibleConnectionsList;}
    else{
        pair<Pair<float,float>,Pair<float,float>> connection;
        float distance = 0;
        auto first = *(coordinatesList.begin());
        if(coordinates == first){
            coordinatesList.erase(coordinatesList.begin());
            if(*(coordinatesList.begin())!=nullptr)first = *(coordinatesList.begin());
            else return possibleConnectionsList;
        }
        distance = distanceBetweenTwoPoints(coordinates,first);
        connection.first = coordinates;
        connection.second = first;
        pair<pair<Pair<float,float>,Pair<float,float>>,float> node;
        node.first = connection;
        node.second = distance;
        possibleConnectionsList.push_back(node);
        if(coordinatesList.size()>0) coordinatesList.erase(coordinatesList.begin());
        return possibleConnections(coordinates,coordinatesList,possibleConnectionsList);
    }
}
auto addVectors(auto from,auto to){
    for(auto i : from)
        to.push_back(i);
    return to;
}
auto areTheSame(vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> elements){
    auto t = *(elements.begin());
    for(auto i : elements) if(t.second != i.second) return false;
    return true;
}
auto orderConnections(vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> elements){
    if(elements.size() == 0) return vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>();
    else if(elements.size() == 1) return elements;
    else if(areTheSame(elements)) return elements;
    else{
        int midVal = (elements.size()) / 2;
        auto mid = *(elements.begin()+midVal-1);
        float pivot = mid.second;
        vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> firstHalf = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>(), secondHalf = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>();
        for(auto i : elements) if(i.second <= pivot) firstHalf.push_back(i); else secondHalf.push_back(i);
        auto ret1 = orderConnections(firstHalf);
        auto ret2 = orderConnections(secondHalf);
        return addVectors(ret2,ret1);
    }
}
auto reverseCoordinates(auto element){
    return pair<Pair<float,float>,Pair<float,float>>(element.second, element.first);
}
auto filterCoordinates(auto mainConnections, auto listedConnections){
    vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> finalElements;
    MyMap<pair<Pair<float,float>,Pair<float,float>>,bool> existingConnections = MyMap<pair<Pair<float,float>,Pair<float,float>>,bool>();
    for(auto i : mainConnections){
        existingConnections.Add(pair<pair<Pair<float,float>,Pair<float,float>>,bool>(i,true));
        existingConnections.Add(pair<pair<Pair<float,float>,Pair<float,float>>,bool>(reverseCoordinates(i),true));
    }
    for(auto i : listedConnections) if(!existingConnections.exist(i.first)) finalElements.push_back(i);
    return finalElements;
}
auto filterInvertedCoordinates(auto listedConnections){
    vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> finalElements, inverted;
    for(int i = 0 ; i < listedConnections.size() ; i++){
        auto comp = listedConnections[i];
        for(int j = i ; j < listedConnections.size() ; j++)
            if(reverseCoordinates(listedConnections[j].first) == comp.first) {listedConnections.erase(listedConnections.begin() + j); j = listedConnections.size();}
    }
    return listedConnections;
}
auto getSet(auto coordinates,const float midX,const float midY){
    if(coordinates.x > midX){
        return (coordinates.y > midY) ? 2 : 3;
    }else{
        return (coordinates.y > midY) ? 1 : 4;
    }
}
template<typename datatype> class graphNode{
    public:
        datatype value;
        pointer<graphNode> next,prev;
        graphNode(): value(NULL){}
        graphNode(datatype value): value{value}{}
};
template<typename datatype> class graph{
    private:
        pointer<graphNode<datatype>> _head,_tail;
        size_t _size;
    public:
        graph(): _head{nullptr},_tail{nullptr},_size{0}{}
        auto empty(){
            return (_size == 0 or not _head or not _tail) ? true : false;
        }
        auto push_back(datatype value){
            auto newNode = new graphNode<datatype>(value);
            if(empty()) _head = _tail = newNode;
            else{
                _tail->next = newNode;
                newNode->prev = _tail;
                _tail = newNode;
                _tail->next = _head;
                _head->prev = _tail;
            }
            _size++;
        }
        auto push_front(datatype value){
            auto newNode = new graphNode<datatype>(value);
            if(empty()) _head = _tail = newNode;
            else{
                _head->prev = newNode;
                newNode->next = _head;
                _head = newNode;
                _head->prev = _tail;
                _tail->next = _head;
            }
            _size++;
        }
        auto front(){
            return _head->value;
        }
        auto back(){
            return _tail->value;
        }
        auto pop_front(){
            if(empty()) return;
            else{
                auto tmp = _head;
                _head = _head->next;
                delete tmp;
                _size--;
            }
        }
        auto pop_back(){
            if(empty()) return;
            else{
                auto tmp = _tail;
                _tail = _tail->prev;
                delete tmp;
                _size--;
            }
        }
        auto size(){
            return _size;
        }
        auto operator=(const graph lst){
            for(int i = 0; i < lst.size();i++){
                this->push_back(lst.front());
                lst.pop_front();
            }
        }
};
auto filterConnections(auto mainCoordinates, auto mainConnections, auto listedConnections){
    vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> finalElements;
    /*vector<pair<Pair<float,float>,int>> set;
    float midX = (maxWidth - minWidth) / 2, midY = (maxHeight - minHeight) / 2;
    for(auto i : mainCoordinates) set.push_back({i,getSet(i)});*/
    graph<Pair<float,float>> coordinates = graph<Pair<float,float>>();
    for(auto i : mainCoordinates) coordinates.push_back(i);
    for(auto i : listedConnections){
        auto temp = coordinates;
        while(temp.front() != i.first) temp.pop_front();

    }
    return finalElements;
}
int main(){
    vector<Pair<float,float>> coordinates = vector<Pair<float,float>>();
    vector<Connection> connections = vector<Connection>();
    graph<Pair<float,float>> coordinatesGraph = graph<Pair<float,float>>();
    int numCoordinates = 0, j = 0;
    maxHeight = maxWidth = 0;
    minHeight = minWidth = 1000;
    cin>>numCoordinates;
    if(numCoordinates < 4) return 0;
    for(auto i = 0 ; i < numCoordinates ; i++){
        float x,y;
        cin>>x>>y;
        maxHeight = max(maxHeight,y);
        maxWidth = max(maxWidth,x);
        minHeight = min(minHeight,y);
        minWidth = min(minWidth,x);
        coordinatesGraph.push_back(Pair<float,float>(x,y));
        coordinates.push_back(Pair<float,float>(x,y));
    }
    for(auto i = 0 ; i < coordinates.size() ; i++){
        Pair<float,float> first, second;
        if(i + 1 >= coordinates.size()){
            first = coordinates[i];
            second = coordinates[0];
        }else{
            first = coordinates[i];
            second = coordinates[i + 1];
        }
        Connection connection = Connection(first,second);
        connection.setLine(first,second);
        connections.push_back(connection);
    }
    vector<vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>> possibleConnection, ordered;
    for(auto i : coordinates){
        vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> connection = possibleConnections(i,coordinates);
        possibleConnection.push_back(connection);
    }
    vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> finalConnections = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>();
    for(auto i : possibleConnection){
        for(auto j : i) finalConnections.push_back(j);
    }
    finalConnections.erase(finalConnections.end());
    vector<pair<Pair<float,float>,Pair<float,float>>> mainConnections = vector<pair<Pair<float,float>,Pair<float,float>>>();
    for(auto i : connections) mainConnections.push_back(pair<Pair<float,float>,Pair<float,float>>(i.getFirst(),i.getLast()));
    finalConnections = orderConnections(finalConnections);
    finalConnections = filterCoordinates(mainConnections,finalConnections);
    finalConnections = filterInvertedCoordinates(finalConnections);
    //finalConnections = filterConnections(coordinates,mainConnections,finalConnections);
    cout<<"Filtered:\n";
    for(auto i : finalConnections){
        cout<<"Connection:\n1) "<<i.first.first<<" 2) "<<i.first.second;
        cout<<"\nDistance: "<<i.second<<endl;
    }
    /*cout<<"Coordinates:\n";
    int coord = 0;
    for(auto i : coordinates){
        cout << coord++ << ") X: " << i.x << " Y: " << i.y << endl;
    }
    cout<<"Connections\n";
    for(auto i : connections){
        cout << i <<endl;
    }*/
}