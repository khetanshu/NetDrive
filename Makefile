all:

	g++ -Iinterfaces/ -Ivo main.cpp testing/ServiceTester.cpp testing/RoutingNodeTester.cpp services/RoutingNode.cpp services/Communication.cpp -o bin/test