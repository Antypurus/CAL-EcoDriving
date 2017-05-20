
#include "OSMParser.h"
#include <unordered_map>
#include "Graph.h"
#include "Location.h"
#include "ElectricVehicle.h"
#include "PROJECT_SETTINGS_MACROS.h"
#include "CoordinateSystem.h"
#include "MATH_CONSTANTS_MACROS.h"
#include <unordered_map>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void pre_kmp(string pattern, vector<int> & prefix)
{
	int m = pattern.length();
	prefix[0] = -1;
	int k = -1;
	for (int q = 1; q < m; q++) {
		while (k > -1 && pattern[k + 1] != pattern[q])
			k = prefix[k];
		if (pattern[k + 1] == pattern[q]) k = k + 1;
		prefix[q] = k;
	}
}

int kmp(string text, string pattern)
{
	int num = 0;
	int m = pattern.length();
	vector<int> prefix(m);
	pre_kmp(pattern, prefix);

	int n = text.length();

	int q = -1;
	for (int i = 0; i < n; i++) {
		while (q > -1 && pattern[q + 1] != text[i])
			q = prefix[q];
		if (pattern[q + 1] == text[i])
			q++;
		if (q == m - 1) {
			//cout <<"pattern occurs with shift" << i-m+1 << endl;
			num++;
			q = prefix[q];
		}
	}
	return num;
}

int editDistance(string pattern, string text)
{
	int n = text.length();
	vector<int> d(n + 1);
	int old, neww;
	for (int j = 0; j <= n; j++)
		d[j] = j;
	int m = pattern.length();
	for (int i = 1; i <= m; i++) {
		old = d[0];
		d[0] = i;
		for (int j = 1; j <= n; j++) {
			if (pattern[i - 1] == text[j - 1]) neww = old;
			else {
				neww = min(old, d[j]);
				neww = min(neww, d[j - 1]);
				neww = neww + 1;
			}
			old = d[j];
			d[j] = neww;
		}
	}
	return d[n];
}

int aproximateSearch(string text, string pattern) {
	stringstream help1;
	stringstream help2;
	string helper1 = "";
	string helper2 = "";
	vector<unsigned int>check;
	help1.str(pattern);
	while (help1.rdbuf()->in_avail() != 0) {
		help1 >> helper1;
		int m = INT_MAX;
		help2.clear();
		help2.str(text);
		while (help2.rdbuf()->in_avail() != 0) {
			help2 >> helper2;
			int i = editDistance(helper1, helper2);
			if (i < m) {
				m = i;
			}
		}
		check.push_back(m);
	}
	unsigned int counter = 0;
	for (int i = 0; i < check.size(); ++i) {
		counter += check[i];
	}
	return counter;
}

void aproximateSearchPoints(string pattern, unordered_map<size_t, EcoDriving::Location::Location> &rechargePoints) {
	system("cls");
	bool found = false;
	for (auto it = rechargePoints.begin();it != rechargePoints.end();++it) {
		if (aproximateSearch(it->second.getName(), pattern) < 5) {
			found = true;
			cout << "Node Name:" << it->second.getName() << "\tNode ID:" << it->first << endl;
		}
	}
	if (!found) {
		printf("Unable To Find A Recharge Point With That Name!\n");
	}
	system("pause");
	return;
}

void exactSearchPoints(string pattern, unordered_map<size_t, EcoDriving::Location::Location> &rechargePoints) {
	system("cls");
	bool found = false;
	for (auto it = rechargePoints.begin();it != rechargePoints.end();++it) {
		if (kmp(it->second.getName(), pattern) == 1) {
			found = true;
			cout << "Node Name:" << it->second.getName() << "\tNode ID:" << it->first << endl;
		}
	}
	if (!found) {
		printf("Unable To Find A Recharge Point With That Name!\n");
	}
	system("pause");
	return;
}

void rechargePointQuerryMenu(unordered_map<size_t, EcoDriving::Location::Location> &rechargePoints) {
	int op = 0;
	while (op == 0) {
		system("cls");

		cout << "1 - List All Recharge Points" << endl;
		cout << "2 - Exact Search For Recharge Points" << endl;
		cout << "3 - Aproximate Search For Recharge Points" << endl;
		cout << "4 - Exit" << endl;

		cout << "Option:";
		cin >> op;

		switch (op)
		{
		case(1):
		{
			op = 0;
			break;
		}
		case(2):
		{
			op = 0;
			break;
		}
		case(3):
		{
			op = 0;
			break;
		}
		case(4):
		{
			return;
		}
		default:
			op = 0;
			break;
		}
	}
	return;
}

using namespace EcoDriving::Linker;

void main(void) {
	GraphViewer *gv = new GraphViewer(1280, 720, false);
	std::unordered_map<size_t, int> referenceTable;
	std::unordered_map<int, size_t> referenceTable2;

	gv->setBackground("background.jpg");

	gv->createWindow(1280, 720);

	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	Linker a;


#if DISPLAY_METRICS
	std::cout << "@Metrics:: Nodes:" << a.nodes.size() << std::endl;
	std::cout << "@Metrics:: Connections:" << a.conections.size() << std::endl;
	std::cout << "@Metrics:: Ways:" << a.ways.size() << std::endl;
	std::cout << "@Metrics:: Node Locations:" << a.locationNodes.size() << std::endl;
#endif

	double minX = a.locationNodes.begin()->second.getCoordinates().x;
	double minY = a.locationNodes.begin()->second.getCoordinates().y;

	for (auto it = a.locationNodes.begin(); it != a.locationNodes.end(); ++it) {
		double keepX = it->second.getCoordinates().x;
		double keepY = it->second.getCoordinates().y;
		if (keepX < minX) {
			minX = keepX;
		}
		if (keepY < minY) {
			minY = keepY;
		}
	}

	EcoDriving::EcoVehicle::ElectricVehicle car(0, 0, 0, 100, 1000);

	int d = 0;
	Graph<EcoDriving::Location::Location> locationGraph;
	Graph<EcoDriving::Location::Location> reverseGraph;
	for (auto it = a.locationNodes.begin(); it != a.locationNodes.end(); ++it) {
		locationGraph.addVertex(it->second);
		reverseGraph.addVertex(it->second);
		referenceTable.insert(std::make_pair(it->first, d));
		referenceTable2.insert(std::make_pair(d, it->first));
		gv->addNode(d, (it->second.getCoordinates().x - minX) * 2, (it->second.getCoordinates().y - minY));
		if (it->second.getRecharge()) {
			gv->setVertexColor(d, "pink");
			gv->setVertexLabel(d, "Recharge Station | ID:" + to_string(d));
		}

#if DISPLAY_METRICS
		cout << "@Metrics:: X:" << it->second.getCoordinates().x << std::endl;
		cout << "@Metrics:: Y:" << it->second.getCoordinates().y << std::endl;
#endif

		d++;
	}

	int c = 0;
	for (auto it = a.conections.begin(); it != a.conections.end(); ++it) {
		std::vector<std::pair<size_t, size_t>> edges = it->second.getEdges();
		for (int i = 0; i < edges.size(); i++) {
			c++;
			EcoDriving::Location::Location src = a.locationNodes[edges[i].first];
			EcoDriving::Location::Location dst = a.locationNodes[edges[i].second];

			double distance = src.getCoordinates().distanceCalculation(dst.getCoordinates());
			double timeToArrival = distance * car.getVelocity();
			double heightDiff = dst.getCoordinates().altitude - src.getCoordinates().altitude;

			double usedBattery = 0;
			if (heightDiff == 0) {
				usedBattery = distance*FLAT_ENERGY_COST;
			}
			else if (heightDiff < 0) {
				usedBattery = -distance*DOWN_HILL_REFENERATION;
			}
			else if (heightDiff > 0) {
				usedBattery = distance*UP_HILL_ENERGY_COST;
			}

			double weight = usedBattery;

#if DISPLAY_METRICS
			cout << "@Metrics:: Weight:" << weight << endl
#endif

				gv->addEdge(c, referenceTable[src.getNodeID()], referenceTable[dst.getNodeID()], EdgeType::DIRECTED);

#if DISPLAY_METRICS
			cout << "@Metrics:: Link:" << src.getNodeID() << "," << dst.getNodeID() << endl;
#endif

			locationGraph.addEdge(src, dst, weight);
			reverseGraph.addEdge(dst, src, weight);
		}
	}

	unordered_map<size_t, EcoDriving::Location::Location>rechargePoints;

	for (auto it = a.conections.begin();it != a.conections.end();++it) {
		auto count = it->second.getEdges();
		for (auto ite = count.begin();ite != count.end();++ite) {
			if (a.locationNodes[ite->first].getRecharge()) {

				a.locationNodes[ite->first].setName(a.ways[it->first].getName());
				rechargePoints.insert(std::make_pair(referenceTable[ite->first], a.locationNodes[ite->first]));

#if DISPLAY_METRICS
				cout << "Has Recharge:" << a.ways[it->first].getName() << "\tNode:" << ite->first << endl;
#endif

			}
			if (a.locationNodes[ite->second].getRecharge()) {

				a.locationNodes[ite->second].setName(a.ways[it->first].getName());
				rechargePoints.insert(std::make_pair(referenceTable[ite->second], a.locationNodes[ite->second]));

#if DISPLAY_METRICS
				cout << "Has Recharge:" << a.ways[it->first].getName() << "\tNode:" << ite->second << endl;
#endif

			}
		}
	}

#if DISPLAY_METRICS
	cout << "@Metrics:: Number of Links:" << c << endl;
#endif

	int op = 0;
	while (op == 0) {
		system("cls");
		cout << " 1 - Route Calculator" << endl;
		cout << " 2 - Recharge Point Queries" << endl;
		cout << " 3 - Exit" << endl;

		cout << "Option:";
		cin >> op;

		switch (op)
		{
		case(1):
		{
			gv->rearrange();

			size_t srcID = 2273202419;
			size_t dstID = 2273202427;

			cout << "Source ID:";
			cin >> srcID;
			cout << "Destination ID:";
			cin >> dstID;

			locationGraph.dijkstraShortestPath(a.locationNodes[referenceTable2[srcID]]);
			EcoDriving::Location::Location str = a.locationNodes[referenceTable2[srcID]];
			EcoDriving::Location::Location end = a.locationNodes[referenceTable2[dstID]];
			vector<EcoDriving::Location::Location> res = locationGraph.getPathToOrigin(str, end);
			Vertex<EcoDriving::Location::Location> check = *(locationGraph.getVertex(str));
			std::vector<EcoDriving::Location::Location> conecCount = locationGraph.bfs(&check);//normal graph list of nodes able to reach
			Vertex<EcoDriving::Location::Location> check2 = *(locationGraph.getVertex(str));
			std::vector<EcoDriving::Location::Location> conecCount2 = reverseGraph.bfs(&check2);//reverse graph list of node able to reach

#if DISPLAY_METRICS
			std::cout << "@Metrics:: Connected Vertexes From Reference Point:" << conecCount.size() << std::endl;
#endif

			if (conecCount.size() == a.locationNodes.size() && conecCount2.size() == a.locationNodes.size()) {
				std::cout << "@GraphInfo:: Conectivity:: This Graph Is Strongly Connected" << std::endl;
			}
			else {
				std::cout << "@GraphInfo:: Conectivity:: This Graph Is Not Connected" << std::endl;
			}

			std::cout << "@GraphInfo:: Path From " << referenceTable2[srcID] << " To " << referenceTable2[dstID] << std::endl;

			std::vector<double>weights;
			bool change = false;
			double counter = 0;

			while (change) {//this code part is disabled due to exception that we cant resolve
				for (int i = 0; i < res.size(); ++i) {
					double dist = res[i].weightTo(res[i + 1]);
					weights.push_back(dist);
				}

				for (int i = 0; i < weights.size(); ++i) {
					counter += weights[i];
					if (counter > car.getBattery()) {
						counter = 0;
						if (!res[i + 1].getRecharge()) {
							change = true;
							locationGraph.removeEdge(res[i], res[i + 1]);
						}
						else {
							change = false;
						}
					}
				}
				locationGraph.dijkstraShortestPath(str);
				res = locationGraph.getPathToOrigin(str, end);
			}//disabled

			for (int i = 0; i < res.size(); i++) {
				cout << "@GraphInfo:: ID:" << res[i].getNodeID() << endl;
				gv->setVertexColor(referenceTable[res[i].getNodeID()], "yellow");
				if (i != res.size() - 1) {
					gv->setVertexLabel(referenceTable[res[i].getNodeID()], "GO HERE");
				}
				else {
					gv->setVertexLabel(referenceTable[res[i].getNodeID()], "START HERE");
				}
			}

			std::cout << "@GraphInfo:: Path Finished" << std::endl;

#if DISPLAY_METRICS
			std::cout << "@Metrics:: Number of Vertexes:" << locationGraph.getNumVertex() << std::endl;
#endif
			system("pause");
			op = 0;
			break;
		}
		case(2):
			rechargePointQuerryMenu(rechargePoints);
			op = 0;
			break;
		case(3):
			exit(0);
		default:
			op = 0;
			break;
		}
	}
	gv->rearrange();
	system("pause");
	return;
}