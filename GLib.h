#define doubleConnection pair<Pair<float,float>,Pair<float,float>>
#define complexConnection vector<pair<doubleConnection,float>>
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
            setLine(first,last);
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
        //This just return the key values
        auto _move(vector<key>* save,auto root)->void{
            if(root != nullptr){
                if(root->left != nullptr) save->push_back(root->left->first);
                if(root->right!= nullptr) save->push_back(root->right->first);
                _move(save,root->left);
                _move(save,root->right);
            }
        }
    public:
        MyMap(): _size{0},_root{nullptr}{}
        MyMap(initializer_list<MyMap<key,value>> list){
            for(auto i : list) this->Add(i);
        }
        auto getKey(){
            return _root->first;
        }
        auto getValue(){
            return _root->second;
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
        auto getKeys(){
            vector<key> keys;
            if(empty()) return keys;
            else{
                _move(&keys,_root);
                return keys;
            }
        }
        ~MyMap(){}
};
auto preOrderConnections(complexConnection items){
    map<float,complexConnection> retValue = map<float,complexConnection>();
    for(auto i : items){
        float distance = i.second;
        retValue[distance].push_back(i);
    }
    return retValue;
}
auto addVectors(auto from,auto to){
    for(auto i : from)
        to.push_back(i);
    return to;
}
auto mergeSort(vector<float> items){
    if(items.size() == 0 or items.size() == 1) return items;
    else{
        int mid = items.size() / 2;
        auto pivot = *(items.begin() + mid);
        vector<float> left, right;
        for(auto i : items)
            if( i <= pivot) left.push_back(i);
            else right.push_back(i);
        return addVectors(mergeSort(left),mergeSort(right));
    }
}
auto orderConnections(complexConnection items){
    auto aux = preOrderConnections(items);
    complexConnection retValue = complexConnection();
    for(auto i : aux) for(auto j : i.second) retValue.push_back(j);
    return retValue;
}
auto distanceBetweenTwoPoints(auto vector1, auto vector2)->double{
    double x1 = vector1.x, x2 = vector2.x, y1 = vector1.y, y2 = vector2.y;
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}
auto possibleConnections(auto coordinates,auto coordinatesList, complexConnection possibleConnectionsList = complexConnection())->complexConnection{
    if(coordinatesList.empty()) {return possibleConnectionsList;}
    else{
        doubleConnection connection;
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
        pair<doubleConnection,float> node;
        node.first = connection;
        node.second = distance;
        possibleConnectionsList.push_back(node);
        if(coordinatesList.size()>0) coordinatesList.erase(coordinatesList.begin());
        return possibleConnections(coordinates,coordinatesList,possibleConnectionsList);
    }
}
auto areTheSame(complexConnection elements){
    auto t = *(elements.begin());
    for(auto i : elements) if(t.second != i.second) return false;
    return true;
}
auto reverseCoordinates(auto element){
    return doubleConnection(element.second, element.first);
}
auto filterCoordinates(auto mainConnections, auto listedConnections){
    complexConnection finalElements;
    MyMap<doubleConnection,bool> existingConnections = MyMap<doubleConnection,bool>();
    for(auto i : mainConnections){
        existingConnections.Add(pair<doubleConnection,bool>(i,true));
        existingConnections.Add(pair<doubleConnection,bool>(reverseCoordinates(i),true));
    }
    for(auto i : listedConnections) if(!existingConnections.exist(i.first)) finalElements.push_back(i);
    return finalElements;
}
auto filterInvertedCoordinates(auto listedConnections){
    complexConnection finalElements, inverted;
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
auto filterChokeConnections(auto connections){
    complexConnection finalElements;
    //Optimizable con pre-calculo
    float count = 0;
    for(auto i : connections) count += i.second;
    float avg = count / connections.size();
    for(auto i : connections) if(i.second <= avg) finalElements.push_back(i);
    return finalElements;
}
auto filterNonValidConnections(auto mainCoordinates, auto mainConnections, auto listedConnections){
    complexConnection finalElements;
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