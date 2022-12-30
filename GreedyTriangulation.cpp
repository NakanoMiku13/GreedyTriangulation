#include<bits/stdc++.h>
using namespace std;
template<typename datatype, typename datatype2>
class Pair{
    public:
        datatype x;
        datatype y;
        Pair(datatype x, datatype2 y){
            this->x = x;
            this->y = y;
        }
        Pair(){
            this->x = (datatype)NULL;
            this->y = (datatype)NULL;
        }
        auto operator==(const auto& other){
            return (this->x == other.x) && (this->y == other.y);
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
        template<typename data,typename data2> friend ostream& operator<<(ostream& out,const Pair<data,data2>& self);
};
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
                //if(begin == NULL or end == NULL) throw 2;
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
};
ostream& operator<<(ostream& out,Connection& self){
    out << "First: " << self.getFirst() << " Second: " << self.getLast() << endl << "Line: \n";
    for(auto i : self.getCoordinates()) out << i << endl;
    return out;
}
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
/*auto orderConnections(vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> elements){
    cout<<"Yet\n";
    if(elements.size() == 1) return elements;
    if(elements.size() == 2){
        vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> aux = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>();
        auto temp1 = *(elements.begin());
        auto temp2 = *(elements.end()-1);
        if(temp1.second > temp2.second){
            aux.push_back(temp2);
            aux.push_back(temp1);
        }else{
            aux.push_back(temp1);
            aux.push_back(temp2);
        }
        return aux;
    }
    if(areTheSame(elements)) {cout<<"Same\n";return elements;}
    cout<<"Yet1\n";
    auto aux = *(elements.begin());
    float pivot = aux.second;
    cout<<"Yet2\n";
    vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> firstHalf,secondHalf;
    firstHalf = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>();
    secondHalf = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>();
    elements.erase(elements.begin());
    cout<<"Yet3\n";
    for(auto i : elements)
        if(pivot < i.second) secondHalf.push_back(i);
        else firstHalf.push_back(i);
    cout<<"Yet4\n";
    firstHalf.push_back(aux);
    cout<<"Pivot: "<<pivot<<endl;
    cout<<"First half\n";
    for(auto i : firstHalf) cout<< i.second<<endl;
    cout<<"second half\n";
    for(auto i : secondHalf) cout<< i.second<<endl;
    auto t1 = orderConnections(firstHalf);
    auto t2 = orderConnections(secondHalf);
    auto ret = addVectors(t2,t1);
    return ret;
}*/
auto orderConnections(vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> elements){
    cout<<"Size: "<<elements.size()<<endl;
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
int main(){
    vector<Pair<float,float>> coordinates = vector<Pair<float,float>>();
    vector<Connection> connections = vector<Connection>();
   int numCoordinates = 0, j = 0;
    cin>>numCoordinates;
    if(numCoordinates < 4) return 0;
    for(auto i = 0 ; i < numCoordinates ; i++){
        double x,y;
        cin>>x>>y;
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
        cout<<"Coordinates to compare: "<<i<<endl;
        cout<<"Coordinates list:\n";
        for(auto j : coordinates) cout<<j<<endl;
        cout<<endl;
        vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> connection = possibleConnections(i,coordinates);
        possibleConnection.push_back(connection);
        cout<<"Push...\n";
    }
    //*(possibleConnection.end()).erase(*(possibleConnection.end()).end());
    cout<<"Cant: "<<possibleConnection.size()<<endl;
    cout<<"Pre-order\n";
    vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>> finalConnections = vector<pair<pair<Pair<float,float>,Pair<float,float>>,float>>();
    for(auto i : possibleConnection){
        for(auto j : i) finalConnections.push_back(j);
    }
    finalConnections.erase(finalConnections.end());
    for(auto i : finalConnections){
        cout<<i.second<<endl;
    }
    cout<<"Ready\n";
    auto temp = orderConnections(finalConnections);
    cout<<"Ordered\n";
    for(auto i : temp){
        cout<<"Connection:\n1) "<<i.first.first<<" 2) "<<i.first.second;
        cout<<"\nDistance: "<<i.second<<endl;
    }
        //sort(i.begin(),i.end());
    //Implementar metodo de ordenamiento
    //sort(possibleConnection.begin(),possibleConnection.end());
    cout<<"Coordinates:\n";
    int coord = 0;
    for(auto i : coordinates){
        cout << coord++ << ") X: " << i.x << " Y: " << i.y << endl;
    }
    cout<<"Connections\n";
    for(auto i : connections){
        cout << i <<endl;
    }
}