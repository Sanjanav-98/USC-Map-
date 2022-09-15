#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// ---------------- PHASE-1 TESTS --------------------------------------------

TEST(TrojanMapStudentTest, GetLat) {
  TrojanMap m;
  EXPECT_EQ(m.GetLat("653725"), 34.0360852);
}

TEST(TrojanMapStudentTest, GetName) {
  TrojanMap m;
  EXPECT_EQ(m.GetName("122659207"), "Crosswalk");
}

TEST(TrojanMapStudentTest, GetID1) {
  TrojanMap m;
  EXPECT_EQ(m.GetID("West Side Church of God"), "358850081");
}

TEST(TrojanMapStudentTest, GetID2) {
  TrojanMap m;
  EXPECT_EQ(m.GetID("West Side Church"), "");
}

TEST(TrojanMapStudentTest, GetLon) {
  TrojanMap TM;
  EXPECT_EQ(TM.GetLon("653725"), -118.3212048);
}

TEST(TrojanMapStudentTest, GetNeighborIDs) {
  TrojanMap TM;
  std::vector<std::string>  out = {"277327731", "1613324102"};
  EXPECT_EQ(TM.GetNeighborIDs("653725"), out);
}

TEST(TrojanMapStudentTest, GetPosition) {
  TrojanMap TM;
  std::pair<double, double> out(34.0302951, -118.2857237);
  EXPECT_EQ(TM.GetPosition("Crosswalk"), out);
}

TEST(TrojanMapTest, FindClosestName) {
  TrojanMap TM;
  EXPECT_EQ(TM.FindClosestName("Rolphs"), "Ralphs");
  EXPECT_EQ(TM.FindClosestName("Targeety"), "Target");
}

// AUTOCOMPLETE

// Test Case 1

TEST(TrojanMapTest, Autocomplete_1) {
  TrojanMap m;
  std::vector<std::string> o1 = { "Universal Truck Driving School", "University S.D.A. Church Food Pantry", "University Seventh Day Adventist Church", "University Park"}; 
  EXPECT_EQ(m.Autocomplete("Univ"), o1); 
}

// Test Case 2

TEST(TrojanMapTest, Autocomplete_2) {
  TrojanMap m;
  std::vector<std::string> o1 = { "Universal Truck Driving School", "University S.D.A. Church Food Pantry", "University Seventh Day Adventist Church", "University Park"}; 
  EXPECT_EQ(m.Autocomplete("UNIV"), o1); // All upper case 
}

// Test Case 3

TEST(TrojanMapTest, Autocomplete_3) {
  TrojanMap m;
  std::vector<std::string> o1 = { "Universal Truck Driving School", "University S.D.A. Church Food Pantry", "University Seventh Day Adventist Church", "University Park"}; 
  EXPECT_EQ(m.Autocomplete("uNiV"), o1); // Upper and lower case
}
// Test Case 4

TEST(TrojanMapTest, Autocomplete_4) {
  TrojanMap m;
  std::vector<std::string> o2 = {}; 
  EXPECT_EQ(m.Autocomplete(""), o2); // Empty string
}

// Test Case 4

TEST(TrojanMapTest, Autocomplete5) {
  TrojanMap m;
  std::vector<std::string> o2 = {}; 
  EXPECT_EQ(m.Autocomplete("qwerty"), o2); // Case not found
}

// Test FindPosition function
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  
  // Test Chick-fil-A
  auto position = m.GetPosition("Chick-fil-A");
  std::pair<double, double> gt1(34.0167334, -118.2825307); // groundtruth for "Chick-fil-A"
  EXPECT_EQ(position, gt1);
  // Test Ralphs
  position = m.GetPosition("Ralphs");
  std::pair<double, double> gt2(34.0317653, -118.2908339); // groundtruth for "Ralphs"
  EXPECT_EQ(position, gt2);
  // Test Target
  position = m.GetPosition("Target");
  std::pair<double, double> gt3(34.0257016, -118.2843512); // groundtruth for "Target"
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = m.GetPosition("XXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
}


TEST(TrojanMapTest, FindPosition1) {
  TrojanMap m;
  std::pair<double, double> gt1(34.0167334, -118.2825307); 
  EXPECT_EQ(m.GetPosition("Chick-fil-A"), gt1); // Chick-fil-A Test Case

  std::pair<double, double> gt2(-1, -1); // Empty String
  EXPECT_EQ(m.GetPosition(""), gt2);

  std::pair<double, double> gt3(-1, -1); // Case not found
  EXPECT_EQ(m.GetPosition("asdf"), gt3);
}

// Test CalculateEditDistance function
TEST(TrojanMapTest, CalculateEditDistance) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("horse", "ros"), 3);
  EXPECT_EQ(m.CalculateEditDistance("intention", "execution"), 5);
}


// -----------------  PHASE 2 ------------------------------------------------------------//

TEST(TrojanMapTest, Dijkstra_invalidInput) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("asd", "qwe");
  std::vector<std::string> gt;  // expect no path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


TEST(TrojanMapTest, CalculateDijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  std::vector<std::string> gt{
 "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469","6813416131",
 "7645318201","6813416130","6813416129","123318563","452688940","6816193777","123408705","6816193774",
 "452688933","452688931","123230412","6816193770","6787470576","4015442011","6816193692","6816193693",
 "6816193694","4015377691","544693739","6816193696","6804883323","6807937309","6807937306","6816193698",
 "4015377690","4015377689","122814447","6813416159","6813405266","4015372488","4015372487","6813405229",
 "122719216","6813405232","4015372486","7071032399","4015372485","6813379479","6813379584","6814769289","5237417650"} ;
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input
  path = m.CalculateShortestPath_Dijkstra("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end());
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, Dijkstra_no_Path) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Dijkstra("Starbucks", "University Park");
  std::vector<std::string> gt;  // expect no path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input
  path = m.CalculateShortestPath_Dijkstra("University Park", "Starbucks");
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapTest, CalculateDijkstra_case2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Dijkstra("23rd Street Cafe", "Fashion District");
  std::vector<std::string> gt{
"2643391587","6816193725","6042989981","6816193726","6042989994","6042989990","3398621876","3398621867",
"6819317149","6789816350","6816175277","1771004850","6816179435","6816179438","6816179441","6816179439",
"122740185","6816179442","6807274422","1771004841","6816179448","1614922718","1771004866","1832234143",
"1832234142","6816179450","214306755","7053658309","6787830204","6787830208","6225907125","63785537",
"2193435046","1378231766","6208583954","1738419620","1732340071","1732340089","6805686613","1732340094",
"3663661794","1732340079","3663661793","6805686622","6816288743","122740034","6816288741","3396349776",
"7864610979","7864610978","7864621790","7864621789","7864621788","7864621787","7864621786","7864621792",
"7864621791","7864621785","123161956","123250775","3574052741","122956976","6805256746","3574052700",
"4012726941","21098546","1866577831","1738419621","72092084","1738419610","7137906862","4012792184",
"8382592037","122840579","9034507187","9034507186","123120142","4012864456","1788084236","7298792413",
"7298792412","6805885798","122648646","4020262090","4020262091","1924840863","122607549","21098548",
"4020262093","21748269","123120136","4020262096","8178538506","8178538507","8178538508","8178538509",
"8178538510","4010398543"} ;
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reverse the input
  path = m.CalculateShortestPath_Dijkstra("Fashion District", "23rd Street Cafe");
  std::reverse(gt.begin(),gt.end());
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}


TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  
  std::vector<std::string> location_names = {"Ralphs", "Chick-fil-A", "KFC"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","KFC"}, {"Ralphs","Chick-fil-A"}, {"KFC","Chick-fil-A"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs", "KFC","Chick-fil-A"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, TopologicalSort1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"The Caribbean Apartments", "Target", "901 Bar & Grill", "Social Security Administration", "Parkside Dining Hall"};
  std::vector<std::vector<std::string>> dependencies = {{"Target","901 Bar & Grill"}, {"Target","Social Security Administration"}, {"The Caribbean Apartments","Social Security Administration"}, {"The Caribbean Apartments","Parkside Dining Hall"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Target", "901 Bar & Grill", "The Caribbean Apartments", "Parkside Dining Hall", "Social Security Administration"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, TopologicalSort2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Food 4 Less", "Ralphs", "Adams-Normandie", "Chevron 2"};
  std::vector<std::vector<std::string>> dependencies = {{"Food 4 Less","Ralphs"}, {"Food 4 Less","Adams-Normandie"}, {"Food 4 Less","Chevron 2"}, {"Chevron 2","Ralphs"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Food 4 Less", "Chevron 2", "Adams-Normandie", "Ralphs"}; 

  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, TopologicalSort3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Ralphs", "Target", "Chipotle Mexican Grill", "CVS", "ChickfilA"};
  std::vector<std::vector<std::string>> dependencies = {{"Target","Chipotle Mexican Grill"}, {"Target","CVS"}, {"Ralphs","CVS"}, {"Ralphs","ChickfilA"}, {"CVS", "Target"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={};
  EXPECT_EQ(result, gt);
}

// BELLMAN FORD ALGORITHM

// Test case 1
// Time taken by function: 8835 ms

TEST(TrojanMapTest, Bellman_Ford_1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Chipotle to CVS Pharmacy
  auto path = m.CalculateShortestPath_Bellman_Ford("Chipotle", "CVS Pharmacy");
  std::vector<std::string> gt{
 "732641023","9446678100","6820935908","216155217","6813411590","1472141024","6813405280","348121864",
 "348121996","6813405275","1732243544","6819179749","4015372463","4015372469","1732243620","6814916523",
 "6814916522","6813379547","6813379546","6813379536","6813379545","6813379544","6813379495","6813379494",
 "3398574883","6813565327","3402810298","6813565328","3088548446"} ; 
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from CVS Pharmacy to Chipotle
  path = m.CalculateShortestPath_Bellman_Ford("CVS Pharmacy", "Chipotle");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 2
// Time taken by function: 8707 ms

TEST(TrojanMapTest, Bellman_Ford_2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Chipotle to CVS Pharmacy
  auto path = m.CalculateShortestPath_Bellman_Ford("Rock & Reillys", "Ralphs");
  std::vector<std::string> gt{
"6045035789","6813360952","6813360954","6814620882","6813360960","6813379480","6813360961",
"6813379584","6813379479","4015372485","7071032399","4015372486","6813405232","122719216",
"6813405229","4015372487","4015372488","6813405266","6813416159","122814447","4015377689",
"4015377690","6816193698","6807937306","6807937309","6804883323","6816193696","544693739",
"4015377691","6816193694","6816193693","6816193692","4015442011","6787470576","6816193770",
"123230412","452688931","452688933","6816193774","123408705","6816193777","452688940","123318563",
"6813416129","6813416130","7645318201","6813416131","8410938469","6805802087","4380040167",
"4380040158","4380040154","2578244375"} ; 
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from CVS Pharmacy to Chipotle
  path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Rock & Reillys");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 3
// Time taken by function: 313 ms
TEST(TrojanMapTest, No_path_Bellman_Ford) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("Starbucks", "Fashion District");
  std::vector<std::string> gt;  // expect no path
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  // Reversed Input
  path = m.CalculateShortestPath_Bellman_Ford("Fashion District", "Starbucks");
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test case 4
// Time taken by function: 15 ms

TEST(TrojanMapTest, Invalid_Input__Bellman_Ford) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto path = m.CalculateShortestPath_Bellman_Ford("qwer", "qwerty");
  std::vector<std::string> gt; 
  std::cout << "My path length: " << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// 5. CYCLE DETECTION

// Test case 1

TEST(TrojanMapTest, CycleDetection1) {
  TrojanMap m;
  std::vector<double> s1 = {-118.2899, -118.26399, 34.030, 34.015};
  auto sub1 = m.GetSubgraph(s1);
  bool result = m.CycleDetection(sub1,s1);
  EXPECT_EQ(result, true);
}

// Test case 2

TEST(TrojanMapTest, CycleDetection2) {
  TrojanMap m;
  std::vector<double> s1 = {-118.2985, -118.2645, 34.0315, 34.0115};
  auto sub1 = m.GetSubgraph(s1);
  bool result = m.CycleDetection(sub1,s1);
  EXPECT_EQ(result, true);
}

// Test case 3

TEST(TrojanMapTest, CycleDetection3) {
  TrojanMap m;
  std::vector<double> square2 = {-118.290, -118.289, 34.030, 34.020};
  auto sub2 = m.GetSubgraph(square2);
  bool result = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result, false);
}

// Test case 4

TEST(TrojanMapTest, CycleDetection4) {
  TrojanMap m;
  std::vector<double> s2 = {-118.290, -118.280, 34.030, 34.020};
  auto sub2 = m.GetSubgraph(s2);
  bool result = m.CycleDetection(sub2,s2);
  EXPECT_EQ(result, true);
}



//6 Traveling Salesman Problem

TEST(TrojanMapTest, TSP1) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP1_invalid) {
  TrojanMap m;
  
  std::vector<std::string> input; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt;
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (result.second.empty()) 
    flag = true;
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP3) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP3_invalid) {
  TrojanMap m;
  
  std::vector<std::string> input; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt;
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (result.second.empty()) // clockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP4) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_3opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}


TEST(TrojanMapTest, TSP4_invalid) {
  TrojanMap m;
  
  std::vector<std::string> input; // Input location ids 
  auto result = m.TravellingTrojan_3opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt;
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (result.second.empty()) // clockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP_BackTracking) {
  TrojanMap m;
  
  std::vector<std::string> input{"6819019976","6820935923","122702233","8566227783","8566227656","6816180153","1873055993","7771782316"}; // Input location ids 
  auto result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6819019976","1873055993","8566227656","122702233","8566227783","6816180153","7771782316","6820935923","6819019976"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);
}

TEST(TrojanMapTest, TSP_Backtracking_invalid) {
  TrojanMap m;
  
  std::vector<std::string> input; // Input location ids 
  auto result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt;
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (result.second.empty()) // clockwise
    flag = true;
  
  EXPECT_EQ(flag, true);
}

// FIND NEARBY


TEST(TrojanMapTest, FindNearby) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarket", "Ralphs", 10, 10);
  std::vector<std::string> ans{"5237417649", "6045067406", "7158034317"};
  EXPECT_EQ(result, ans);
}

TEST(TrojanMapTest, FindNearby2) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarket", "Ralphs", 10, 1);
  std::vector<std::string> ans{"5237417649"};
  EXPECT_EQ(result, ans);
}


TEST(TrojanMapTest, FindNearby3) {
  TrojanMap m;
  
  auto result = m.FindNearby("supermarke", "Ralphs", 10, 1);
  std::vector<std::string> ans;
  EXPECT_EQ(result, ans);
}

TEST(TrojanMapTest, FindNearby4) {
  TrojanMap m;
  
  auto result = m.FindNearby("", "", 10, 1);
  std::vector<std::string> ans;
  EXPECT_EQ(result, ans);
}