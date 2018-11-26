FLAGS = -std=c++11 -Iinterfaces/ -Ivo -Itesting_interfaces/

all: 
	g++ $(FLAGS) routingMain.cpp services/RoutingNode.cpp services/Communication.cpp -o bin/router
	# g++ $(FLAGS) clientMain.cpp services/ClientNode.cpp services/Communication.cpp -o bin/client
	# g++ $(FLAGS) main.cpp testing/ServiceTester.cpp testing/RoutingNodeTester.cpp services/RoutingNode.cpp services/Communication.cpp -o bin/test