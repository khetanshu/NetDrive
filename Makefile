FLAGS = -std=c++11 -Iinterfaces/ -Ivo

all: 
	g++ $(FLAGS) testing/RoutingNodeTester.cpp services/RoutingNode.cpp services/Communication.cpp -o bin/router
	g++ $(FLAGS) testing/ClientNodeTester.cpp services/ClientNode.cpp services/Communication.cpp -o bin/client
	# g++ -std=c++11 -Iinterfaces/ -Ivo main.cpp testing/ServiceTester.cpp testing/RoutingNodeTester.cpp services/RoutingNode.cpp services/Communication.cpp -o bin/test