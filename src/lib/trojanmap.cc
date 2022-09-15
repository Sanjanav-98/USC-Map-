#include "trojanmap.h"

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string& id) {
    double lat = 0.0;
    for (auto j = data.begin(); j != data.end(); j++){
      std::string id1 = data[j->first].id;
      if(id1 == id ){
        lat = data[j->first].lat;
    }
  }
    return lat;
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string& id) { 
    double lon = 0.0;
    for (auto j = data.begin(); j != data.end(); j++){
    std::string id1 = data[j->first].id;
    if(id1 == id ){
      lon = data[j->first].lon;
    }
  }
    return lon;
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return "NULL".
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string& id) { 
    std::string name = "";
    for (auto j = data.begin(); j != data.end(); j++){
      std::string id1 = data[j->first].id;
      if(id1 == id ){
        name = data[j->first].name;
    }
  }
    return name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return an empty vector.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string& id) {

    std::vector<std::string> n_id;
    for (auto j = data.begin(); j != data.end(); j++){
    std::string id1 = data[j->first].id;
    if(id1 == id ){
      n_id = data[j->first].neighbors;
    }
  }
    return n_id;
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string& name) {
  std::string id1 = "";
  if(name == ""){
    return id1;
  }
  for (auto j = data.begin(); j != data.end(); j++){
      std::string name1 = data[j->first].name;
      if(name1 == name ){
        id1 = data[j->first].id;
    }
  }
    return id1;
}

/**
 * GetPosition: Given a location name, return the position. If id does not exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> pos(-1, -1);
  std::string id = GetID(name) ;
    if(id == "" ){
      return pos;
    } 
    pos.first = GetLat(id);
    pos.second = GetLon(id);
    
  return pos;
}


/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * 
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b){

    int len1 = a.size();
    int len2 = b.size();
        
    int dp[len1+1][len2+1];

    for(auto i=0;i<=len1;i++)
    {
      dp[i][0]=i;
    }
        
    for(auto i=1;i<=len2;i++)
    {
      dp[0][i]=i;
    }
        
    for(auto i=1;i<=len1;i++)
    {
      for(int j=1;j<=len2;j++)
      {
        if(a[i-1]==b[j-1])
          dp[i][j]=dp[i-1][j-1];
        else{
          dp[i][j]=std::min(dp[i-1][j],dp[i][j-1]);
          dp[i][j]=1+std::min(dp[i][j],dp[i-1][j-1]);
        }
      }
    }
    return dp[len1][len2];
  }

/**
 * FindClosestName: Given a location name, return the name with smallest edit distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string temp = "";
  int res = INT_MAX;
  for(auto j = data.begin(); j != data.end(); j++){
    std::string name1 = data[j->first].name;
    int dist = CalculateEditDistance(name1, name);
    if (dist<res){
      res = dist;
      temp = name1;
    }

  }
  return temp;
}


/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  if (name == "") {
    return results;}
  transform(name.begin(), name.end(), name.begin(), ::tolower);
  for(auto j = data.begin(); j != data.end(); j++){
    std::string str_orig = data[j->first].name;
    std::string temp_str = data[j->first].name;
    transform(temp_str.begin(), temp_str.end(), temp_str.begin(), ::tolower);
    if(temp_str.find(name) == 0){
      results.push_back(str_orig);
    }
  }
  return results;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < int(path.size())-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  
  std::vector<std::string> path;
  std::string start = GetID(location1_name);
  std::string end = GetID(location2_name); 
  if(start == "" || end == ""){
    return path;
  }
  std::priority_queue <std::pair<double,std::string>,std::vector<std::pair<double,std::string>>,std::greater<std::pair<double,std::string>>> pq;                 //Priority queue to implement Heap with <distance,node ID>
  std::unordered_map <std::string,double> dist;                 
  std::unordered_map <std::string,std::string> pre;   
  std::unordered_map <std::string,bool> visited;        
    
  for(auto j = data.begin(); j != data.end(); j++){
      dist[data[j->first].id] = DBL_MAX;
      pre[data[j->first].id] = "";
      visited[data[j->first].id] = false;
  }
    
  dist[start] = 0;
  pq.push(std::make_pair(dist[start],start));
  
  while(!pq.empty()){
    std::pair<double,std::string> pair_pq = pq.top();
    std::string current_id = pair_pq.second;
    pq.pop();
    if(current_id!=end){
      if(CalculateDistance(current_id,start)>dist[current_id]){
        continue;
      }
      else if(visited[current_id]){
        continue;
      }
      else{
        visited[current_id] = true;
        std::vector <std::string> neighbor_id_list  = data[current_id].neighbors;
        for(auto n : neighbor_id_list){
            double new_dist = dist[current_id] + CalculateDistance(current_id,n);
             if(new_dist < dist[n]){
               dist[n] = new_dist;
               pre[n] = current_id;   
               pq.push(std::make_pair(dist[n],n));          
              }
        }
      }
    } 
    else{
      visited[end] = true;
      break;
    }
  }
  if(!visited[end]){
    return path;   
  }
  for(auto node = end; node!= start; node = pre[node])
  {
    path.push_back(node);
  }
  path.push_back(start);
  std::reverse(path.begin(),path.end());
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Do the early termination when there is no change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){

  std::string start = GetID(location1_name);
  std::string end = GetID(location2_name);
  std::vector<std::string> path;
  if(start=="" || end=="") return {};
  if(start == end) return {start};

  std::unordered_map<std::string,double> dist;
  std::unordered_map<std::string,std::string> pre;

  for(auto j = data.begin(); j != data.end(); j++){
    dist[data[j->first].id] = DBL_MAX;
    pre[data[j->first].id] = "";
  }

  dist[start] = 0;
  bool start_flag= true;

  if(start!=end){
    for(auto i = data.begin(); i != data.end(); i++){
      for(auto j = data.begin(); j != data.end(); j++){
        std::string cuurent_id = data[j->first].id;
        std::vector<std::string> neighbor_id_list = data[j->first].neighbors; 
        for (auto n:neighbor_id_list){
          double dist1 = CalculateDistance(cuurent_id,n); //w
          if(dist[cuurent_id] + dist1 < dist[n]){
            dist[n] = dist[cuurent_id] + dist1;
            pre[n] = cuurent_id;
            start_flag= false;
          }
        }
      }
      if(start_flag == true){
        break;
      }
      start_flag = true;
    }     
  }

  if (dist[end] == DBL_MAX){
    return path;
  } 
  
  for (auto p1 = end; p1 != start; p1 = pre[p1]){
    path.push_back(p1);
  }
  path.push_back(start);

  std::reverse(path.begin(), path.end());
  return path;
  
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  if(location_ids.size() == 0){
    records.first = 0;
    std::vector<std::vector<std::string>> temp;
    records.second = temp;
  }
  if(location_ids.size()<2) {
    return records;
  }
  std::vector<std::string> locations;
  std::string src = location_ids[0];
  std::vector<std::vector<std::string>> final_path;
  std::vector<std::string> current_path;

  for(auto loc : location_ids){
    if (loc != src){
      locations.push_back(loc);
    }      
  }

  double min_dist = DBL_MAX;

  do {
    double current_dist = 0;
    std::string current_loc = src;
    for (int i = 0; i < locations.size(); i++) {
      current_dist += CalculateDistance(current_loc,locations[i]);
      current_loc = locations[i];
    }
    current_dist += CalculateDistance(current_loc,src);
    if(min_dist>current_dist)
    {
      current_path.clear();
      current_path.push_back(src);

      for(auto loc: locations)
        current_path.push_back(loc);
        current_path.push_back(src);
        final_path.push_back(current_path);
    }
    min_dist = min_dist < current_dist ? min_dist : current_dist;
    } while (
        next_permutation(locations.begin(), locations.end()));

  records.first = min_dist;
  records.second = final_path;
  return records;
}

std::vector<std::string> TrojanMap::create_path(std::vector<std::string> &location_ids,std::vector<int> current_path){
  std::vector<std::string> path_created(location_ids.size()); 
  int j = 0;
  for(auto i = 0; i<current_path.size(); i++){
    j = current_path[i];
    path_created[i]= location_ids[j];
  }
  path_created.push_back(location_ids[0]);
  return path_created;
}

void TrojanMap::TravellingTrojan_Backtracking_helper(int start,std::vector<std::string> &location_ids,int current_id, double current_cost,std::vector<int> &current_path, double &min_cost, std::vector<int> &min_path, std::pair<double, std::vector<std::vector<std::string>>> &records){
  std::vector<std::string> path_created(location_ids.size());
  if(current_path.size()==location_ids.size()){
    
    double final_cost = current_cost + CalculateDistance(location_ids[current_id],location_ids[start]);
    if(final_cost < min_cost){
      records.first = final_cost;
      min_cost = final_cost;
      min_path = current_path;
      path_created = create_path(location_ids,current_path);
      records.first = min_cost;
      records.second.push_back(path_created);
    } 
    return;
  }
  if(current_cost>records.first){
    return;
  }
  for(int j = 0; j < location_ids.size(); j++){
    auto path_itr = std::find(current_path.begin(), current_path.end(), j);
    if(path_itr == current_path.end()){
      current_path.push_back(j);
      TravellingTrojan_Backtracking_helper(start, location_ids, j, current_cost + CalculateDistance(location_ids[current_id],location_ids[j]), current_path, min_cost, min_path,records);
      current_path.pop_back();
      }
  }
}
	

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  
  int start = 0;
  if(location_ids.size()<2) {
    return records;
  }
  std::vector<int> current_path = {0};
  std::vector<int> min_path;
  double min_cost = DBL_MAX;
  records.first= min_cost;
  TravellingTrojan_Backtracking_helper(start,location_ids,start, 0.0, current_path,min_cost,min_path,records);
  return records;
}


std::vector<std::string> TrojanMap::twoOptSwap(const std::vector<std::string> &route, int i, int k) {
  std::vector<std::string> res(route);
  std::reverse(res.begin() + i, res.begin() + k + 1);
  return res;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){

  std::pair<double, std::vector<std::vector<std::string>>> records;
  if(location_ids.size() == 0){
    records.first = 0;
    std::vector<std::vector<std::string>> temp;
    records.second = temp;
  }
    if(location_ids.size()<2) {
    return records;
  }

  std::vector<std::string> existing_route = location_ids;
  existing_route.push_back(location_ids[0]);
  bool improve = true;

  while(improve){
    start_again:
    improve = false;
    double best_distance = CalculatePathLength(existing_route);
    for(int i = 1; i <= location_ids.size() - 2; i++){
      for(int k = i + 1; k <= location_ids.size() - 1; k++){
        auto new_route = twoOptSwap(existing_route, i, k);
        double new_dist = CalculatePathLength(new_route);
        if(new_dist < best_distance){
          existing_route = new_route;
          best_distance = new_dist;
          records.first = best_distance;
          records.second.push_back(existing_route);
          improve = true;
          goto start_again;
        }
      }
    }
  }
  return records;
}


// 3-opt Traveling Salesman Problem Extra credit

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(std::vector<std::string> &location_ids){
  
  std::pair<double, std::vector<std::vector<std::string>>> records;
  if(location_ids.size()<2) {
    return records;
  }
  std::vector<std::vector<std::string>> final_path;
  std::vector<std::string> current_path;
  for(auto location:location_ids){
    current_path.push_back(location);
  }
  current_path.push_back(location_ids[0]);
  double current_dist = CalculatePathLength(current_path);
  final_path.push_back(current_path);

  bool improve = false;
  while(!improve){
    improve = true;
    
    for(auto i=0;i<current_path.size()-3;i++){
      for(auto j=i+1;j<current_path.size()-2;j++){
        int k = current_path.size() - 2;
        std::vector<std::string> part_1(current_path.begin(),current_path.begin()+i+1);
        std::vector<std::string> part_2(current_path.begin()+i+1,current_path.begin()+j+1);
        std::vector<std::string> part_3(current_path.begin()+j+1,current_path.begin()+k+1);

        int index = 0;
        std::vector<std::string> path_1;
        path_1.insert(path_1.end(),part_1.begin(),part_1.end());
        path_1.insert(path_1.end(),part_3.begin(),part_3.end());
        path_1.insert(path_1.end(),part_2.begin(),part_2.end());
        path_1.push_back(path_1[0]);

        double dist_1 = CalculatePathLength(path_1);
        if(dist_1 < current_dist){
          index = 1;
          current_dist = dist_1;
        }

        std::vector<std::string> path_2;
        path_2.insert(path_2.end(),part_1.begin(),part_1.end());
        path_2.insert(path_2.end(),part_3.begin(),part_3.end());
        path_2.insert(path_2.end(),part_2.begin(),part_2.end());
        std::reverse(path_2.begin()+j+1,path_2.begin()+k+1);
        path_2.push_back(path_2[0]);
        double dist_2 = CalculatePathLength(path_2);
        if(dist_2 < current_dist){
          index = 2;
          current_dist = dist_2;
        }
        std::vector<std::string> path_3;
        path_3.insert(path_3.end(),part_1.begin(),part_1.end());
        path_3.insert(path_3.end(),part_3.begin(),part_3.end());
        path_3.insert(path_3.end(),part_2.begin(),part_2.end());
        std::reverse(path_3.begin()+i+1,path_3.begin()+j+1);
        path_3.push_back(path_3[0]);
        double dist_3 = CalculatePathLength(path_3);
        if(dist_3 < current_dist){
          index = 3;
          current_dist = dist_3;
        }

        std::vector<std::string> path_4;
        path_4.insert(path_4.end(),part_1.begin(),part_1.end());
        path_4.insert(path_4.end(),part_3.begin(),part_3.end());
        path_4.insert(path_4.end(),part_2.begin(),part_2.end());
        std::reverse(path_4.begin()+i+1,path_4.begin()+k+1);
        path_4.push_back(path_4[0]);
        double dist_4 = CalculatePathLength(path_4);
        if(dist_4 < current_dist){
          index = 4;
          current_dist = dist_4;
        }

        std::vector<std::string> path_5;
        path_5.insert(path_5.end(),part_1.begin(),part_1.end());
        path_5.insert(path_5.end(),part_2.begin(),part_2.end());
        path_5.insert(path_5.end(),part_3.begin(),part_3.end());
        std::reverse(path_5.begin()+j+1,path_5.begin()+k+1);
        path_5.push_back(path_5[0]);
        double dist_5 = CalculatePathLength(path_5);
        if(dist_5 < current_dist){
          index = 5;
          current_dist = dist_5;
        }

        std::vector<std::string> path_6;
        path_6.insert(path_6.end(),part_1.begin(),part_1.end());
        path_6.insert(path_6.end(),part_2.begin(),part_2.end());
        path_6.insert(path_6.end(),part_3.begin(),part_3.end());
        std::reverse(path_6.begin()+i+1,path_6.begin()+j+1);
        path_6.push_back(path_6[0]);
        double dist_6 = CalculatePathLength(path_6);
        if(dist_6 < current_dist){
          index = 6;
          current_dist = dist_6;
        }

        std::vector<std::string> path_7;
        path_7.insert(path_7.end(),part_1.begin(),part_1.end());
        path_7.insert(path_7.end(),part_2.begin(),part_2.end());
        path_7.insert(path_7.end(),part_3.begin(),part_3.end());
        std::reverse(path_7.begin()+i+1,path_7.begin()+j+1);
        std::reverse(path_7.begin()+j+1,path_7.begin()+k+1);
        path_7.push_back(path_7[0]);
        double dist_7 = CalculatePathLength(path_7);
        if(dist_7 < current_dist){
          index = 7;
          current_dist = dist_7;
        }
        switch (index)
        {
          case 1: current_path = std::move(path_1);break;
          case 2: current_path = std::move(path_2);break;
          case 3: current_path = std::move(path_3);break;
          case 4: current_path = std::move(path_4);break;
          case 5: current_path = std::move(path_5);break;
          case 6: current_path = std::move(path_6);break;
          case 7: current_path = std::move(path_7);break;
        }
        if(index!=0){
          final_path.push_back(current_path);
          improve = false;
        }
      }
    }
  }
  return std::pair<double, std::vector<std::vector<std::string>>>(current_dist,final_path);
}


/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    location_names_from_csv.push_back(line);
  }  
  fin.close();
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::string temp;
    std::vector<std::string> dependencies;
    while(getline(s, temp, ',')) {
      dependencies.push_back(temp);
    }
  dependencies_from_csv.push_back(dependencies);
  }
  fin.close();
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies. If there is no way to do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */

void TrojanMap::topologicalsort_helper(std::string loc,std::map<std::string, bool> &visited,std::stack<std::string> &loc_stack,std::unordered_map<std::string, std::vector<std::string>> adj ){
  visited[loc] = true;
  std::vector<std::string> adj_list = adj[loc];
  for(auto i:adj_list){
    if(!visited[i]){
      topologicalsort_helper(i,visited,loc_stack,adj);
    }
  }
  loc_stack.push(loc);
}

std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;

  if(locations.size() <= 1){
    return result;
  } 

  //creating DAG

  std::unordered_map<std::string, std::vector<std::string>> adj;

  for(auto l:locations){
    std::vector<std::string> temp;
    adj[l] = temp;
  }

  for(auto d:dependencies){
    if(adj.find(d[1]) != adj.end()){
      std::vector<std::string> temp_list = adj[d[1]];
      if(std::find(temp_list.begin(), temp_list.end(), d[0]) != temp_list.end()){
        std::vector<std::string> temp_res;
        return temp_res;
      }
    }
    adj[d[0]].push_back(d[1]);
  }

  std::map<std::string, bool> visited;

  std::stack<std::string> loc_stack;

  for(auto l:locations){
    visited[l] = false;
  }
  for (int i = 0; i < locations.size(); i++)
    if (visited[locations[i]] == false)
      topologicalsort_helper(locations[i], visited, loc_stack, adj);
 
    while(!loc_stack.empty()) {
        result.push_back(loc_stack.top()); 
        loc_stack.pop();
    }

  return result;                                                     
}                                               


/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  std::vector<std::string> square_id = GetSubgraph(square);
  if(std::find(square_id.begin(), square_id.end(), id) != square_id.end()) {
    return true;
  } else {
    return false;
  }
}


/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  double ver1 = square[0];
  double ver2 = square[1];
  double ver3 = square[2];
  double ver4 = square[3];

  for(auto j = data.begin(); j != data.end(); j++){
    if((data[j->first].lon)>ver1 && (data[j->first].lon)<ver2){
      if((data[j->first].lat)<ver3 && (data[j->first].lat)>ver4){
        subgraph.push_back(data[j->first].id);
      }
    }
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<std::string>} subgraph: list of location ids in the square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */
bool TrojanMap::hasCycle(std::string current_id,std::unordered_map<std::string, bool> &visited, std::string parent_id){
  visited[current_id] = true;
  for(auto n:data[current_id].neighbors){
    if(visited.find(n) != visited.end()){ //to check if the neighbor is in the area
      if(visited[n] == false){
        if(hasCycle(n,visited,current_id)){
          return true;
        }
      }else if((n!=parent_id) && (visited[n]== true)){
          return true;
      }
    }
  }
  return false;
}

bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  std::unordered_map<std::string, bool> visited;

  for(auto id_i:subgraph){
    visited[id_i] = false;
  }

  for(auto id_itr:subgraph){
    if(visited[id_itr] == false){
      if (hasCycle(id_itr,visited,"")){
        return true;
      }
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r, 
 * find all locations in class C on the map near L with the range of r and return a vector of string ids
 * 
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  std::vector<std::string> result_temp;
  std::string current_id = GetID(name);
  if(current_id == ""){
    return res;
  }
  std::map<double, std::string, std::greater<double>> attributes_name_id;

  for(auto j = data.begin(); j != data.end(); j++){
    for(auto att:data[j->first].attributes){
      if(att == attributesName){
          double res = CalculateDistance(current_id,data[j->first].id);
          if((res<=r) &&(res!=0)){
            attributes_name_id[res] = data[j->first].id;
          }
      }
    }
  }

  for(auto m:attributes_name_id){
    result_temp.push_back(m.second);
  }
  std::reverse(result_temp.begin(), result_temp.end());
  if(result_temp.size()>k){
    res = {result_temp.begin(), result_temp.begin() + k};
  }else{
    res = result_temp;
  }
  return res;
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0]))
          n.attributes.insert(word);
        if (isdigit(word[0]))
          n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
