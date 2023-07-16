#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <climits>
#include <sstream>
using namespace std;
class Graph_Metro {
private:
    class Vertex {
    public:
        std::unordered_map<std::string, int> nbrs;
    };

    std::unordered_map<std::string, Vertex> vtces;

public:
    int numVertex() {
        return vtces.size();
    }

    int num_of_Edges() {
        int count = 0;
        for (const auto& entry : vtces) {
            count += entry.second.nbrs.size();
        }
        return count / 2;
    }

    bool check_containsVertex(const std::string& vname) {
        return vtces.count(vname) > 0;
    }

    void add_a_Vertex(const std::string& vname) {
        Vertex vtx;
        vtces[vname] = vtx;
    }

    void remove_a_Vertex(const std::string& vname) {
        Vertex vtx = vtces[vname];
        std::vector<std::string> keys;
        for (const auto& entry : vtx.nbrs) {
            keys.push_back(entry.first);
        }

        for (const std::string& key : keys) {
            Vertex nbrVtx = vtces[key];
            nbrVtx.nbrs.erase(vname);
        }

        vtces.erase(vname);
    }

    void add_a_Edge(const std::string& vname1, const std::string& vname2, int value) {
        if (!check_if_containsEdge(vname1, vname2)) {
            vtces[vname1].nbrs[vname2] = value;
            vtces[vname2].nbrs[vname1] = value;
        }
    }

    bool check_if_containsEdge(const std::string& vname1, const std::string& vname2) {
        if (vtces.count(vname1) == 0 || vtces.count(vname2) == 0 ||
            vtces[vname1].nbrs.count(vname2) == 0) {
            return false;
        }
        return true;
    }

    void remove_a_Edge(const std::string& vname1, const std::string& vname2) {
        if (check_if_containsEdge(vname1, vname2)) {
            vtces[vname1].nbrs.erase(vname2);
            vtces[vname2].nbrs.erase(vname1);
        }
    }

    void display_the_Map() {
        std::cout << "\t Delhi Metro Map" << std::endl;
        std::cout << "\t------------------" << std::endl;
        for (const auto& entry : vtces) {
            std::cout << entry.first << " =>" << std::endl;
            const Vertex& vtx = entry.second;
            for (const auto& nbr : vtx.nbrs) {
                std::cout << "\t" << nbr.first << "\t" << vtx.nbrs.at(nbr.first) << std::endl;
            }
        }
        std::cout << "\t------------------" << std::endl;
    }

    void display_all_Stations() {
        std::cout << std::endl << "***********************************************************************" << std::endl;
        int i = 1;
        for (const auto& entry : vtces) {
            std::cout << i << ". " << entry.first << std::endl;
            i++;
        }
        std::cout << std::endl << "***********************************************************************" << std::endl;
    }

    bool if_hasPath(const std::string& vname1, const std::string& vname2, std::unordered_map<std::string, bool>& processed) {
        if (check_if_containsEdge(vname1, vname2)) {
            return true;
        }

        processed[vname1] = true;

        const Vertex& vtx = vtces[vname1];
        for (const auto& nbr : vtx.nbrs) {
            if (!processed.count(nbr.first)) {
                if (if_hasPath(nbr.first, vname2, processed)) {
                    return true;
                }
            }
        }

        return false;
    }

    class DijkstraPair {
    public:
        std::string vname;
        std::string psf;
        int cost;

        DijkstraPair() : vname(""), psf(""), cost(0) {}

        DijkstraPair(const std::string& v, const std::string& p, int c) : vname(v), psf(p), cost(c) {}

        bool operator<(const DijkstraPair& other) const {
            return cost > other.cost;
        }
    };

    int dijkstra(const std::string& src, const std::string& des, bool nan) {
        int val = 0;
        std::unordered_map<std::string, DijkstraPair> map;

        std::priority_queue<DijkstraPair> pq;
        for (const auto& entry : vtces) {
            const std::string& key = entry.first;
            DijkstraPair np(key, "", INT_MAX);

            if (key == src) {
                np.cost = 0;
                np.psf = key;
            }

            pq.push(np);
            map[key] = np;
        }

        while (!pq.empty()) {
            DijkstraPair rp = pq.top();
            pq.pop();

            if (rp.vname == des) {
                val = rp.cost;
                break;
            }

            map.erase(rp.vname);

            const Vertex& v = vtces[rp.vname];
            for (const auto& nbr : v.nbrs) {
                if (map.count(nbr.first) > 0) {
                    int oc = map[nbr.first].cost;
                    int nc;
                    if (nan) {
                        nc = rp.cost + 20 + 4 * v.nbrs.at(nbr.first);
                    } else {
                        nc = rp.cost + v.nbrs.at(nbr.first);
                    }

                    if (nc < oc) {
                        DijkstraPair gp(nbr.first, rp.psf + nbr.first, nc);
                        pq.push(gp);
                        map[nbr.first] = gp;
                    }
                }
            }
        }
        return val;
    }

    class Pair {
    public:
        std::string vname;
        std::string psf;
        int min_dis;
        int min_time;

        Pair(const std::string& v, const std::string& p, int d, int t) : vname(v), psf(p), min_dis(d), min_time(t) {}
    };

    void findMinimumSpanningTree(const std::string& src) {
        std::unordered_map<std::string, int> dist;
        std::unordered_map<std::string, bool> visited;
        std::unordered_map<std::string, std::string> parent;
        int totalDistance = 0;

        for (const auto& entry : vtces) {
            const std::string& key = entry.first;
            dist[key] = INT_MAX;
            visited[key] = false;
        }

        dist[src] = 0;
        parent[src] = "";

        for (int i = 0; i < numVertex() - 1; ++i) {
            std::string currVertex = getMinimumDistanceVertex(dist, visited);
            visited[currVertex] = true;

            const Vertex& vtx = vtces[currVertex];
            for (const auto& nbr : vtx.nbrs) {
                const std::string& nbrVertex = nbr.first;
                int weight = vtx.nbrs.at(nbrVertex);
                if (!visited[nbrVertex] && weight < dist[nbrVertex]) {
                    dist[nbrVertex] = weight;
                    parent[nbrVertex] = currVertex;
                }
            }
        }

        std::cout << "Minimum path and and total distance required to cover all stations:" << std::endl;
        for (const auto& entry : parent) {
            if (entry.second != "") {
                std::cout << entry.second << " -> " << entry.first << std::endl;
                totalDistance += vtces[entry.second].nbrs[entry.first];
            }
        }
        std::cout << "Total Distance: " << totalDistance << " Kilo_meters" << std::endl;
    }

    std::string getMinimumDistanceVertex(const std::unordered_map<std::string, int>& dist, const std::unordered_map<std::string, bool>& visited) {
        int minDist = INT_MAX;
        std::string minVertex;

        for (const auto& entry : vtces) {
            const std::string& vertex = entry.first;
            if (!visited.at(vertex) && dist.at(vertex) < minDist) {
                minDist = dist.at(vertex);
                minVertex = vertex;
            }
        }

        return minVertex;
    }

    std::string getMinimumDistance(const std::string& src, const std::string& dst) {
        int min = INT_MAX;
        std::string ans = "";
        std::unordered_map<std::string, bool> processed;
        std::queue<Pair> q;

        Pair sp(src, src + "  ", 0, 0);
        q.push(sp);

        while (!q.empty()) {
            Pair rp = q.front();
            q.pop();

            if (processed.count(rp.vname) > 0) {
                continue;
            }

            processed[rp.vname] = true;

            if (rp.vname == dst) {
                int temp = rp.min_dis;
                if (temp < min) {
                    ans = rp.psf;
                    min = temp;
                }
                continue;
            }

            const Vertex& rpvtx = vtces[rp.vname];
            for (const auto& nbr : rpvtx.nbrs) {
                if (processed.count(nbr.first) == 0) {
                    Pair np(nbr.first, rp.psf + nbr.first + "  ", rp.min_dis + rpvtx.nbrs.at(nbr.first), rp.min_time + 120 + 40 * rpvtx.nbrs.at(nbr.first));
                    q.push(np);
                }
            }
        }
        ans += "  -> Distance: " + std::to_string(min) + " kilo_meters";
        return ans;
    }

    std::vector<std::string> print_station_Codelist() {
        std::cout << "List of stations along with their codes:\n";

        std::vector<std::string> keys;
        for (const auto& entry : vtces) {
            keys.push_back(entry.first);
        }

        int i = 1, j = 0, m = 1;
        std::string temp, code;
        std::vector<std::string> codes(keys.size());
        char c;
        for (const std::string& key : keys) {
            std::istringstream iss(key);
            codes[i - 1] = "";
            j = 0;

            while (iss >> temp) {
                c = temp[0];

                while (c > 47 && c < 58) {
                    codes[i - 1] += c;
                    j++;
                    c = temp[j];
                }

                if ((c < 48 || c > 57) && c < 123)
                    codes[i - 1] += c;
            }

            if (codes[i - 1].length() < 2)
                codes[i - 1] += std::toupper(temp[1]);

            std::cout << i << ". " << key << "\t";
            if (key.length() < (22 - m))
                std::cout << "\t";
            if (key.length() < (14 - m))
                std::cout << "\t";
            if (key.length() < (6 - m))
                std::cout << "\t";
            std::cout << codes[i - 1] << std::endl;

            i++;
            if (i == pow(10, m))
                m++;
        }

        return codes;
    }

    void find_min_spanning_tree() {
        std::vector<std::string> keys;
        for (const auto& entry : vtces) {
            keys.push_back(entry.first);
        }
        // This is the vector of keys the vertices
    }
};

int main() {
    Graph_Metro g;
    g.add_a_Vertex("Dwarka");
    g.add_a_Vertex("Janakpuri");
    g.add_a_Vertex("Palam");
    g.add_a_Vertex("IGI Airport");
    g.add_a_Vertex("Aerocity");
    g.add_a_Vertex("Vasant Vihar");
    g.add_a_Vertex("Dhaula Kuan");
    g.add_a_Vertex("Karol Bagh");
    g.add_a_Vertex("Connaught Place");
    g.add_a_Vertex("Lajpat Nagar");
    g.add_a_Vertex("Nehru Place");
    g.add_a_Vertex("Greater Kailash");

    g.add_a_Edge("Dwarka", "Janakpuri", 6);
    g.add_a_Edge("Dwarka", "Palam", 3);
    g.add_a_Edge("Palam", "IGI Airport", 5);
    g.add_a_Edge("IGI Airport", "Aerocity", 3);
    g.add_a_Edge("IGI Airport", "Vasant Vihar", 8);
    g.add_a_Edge("Vasant Vihar", "Dhaula Kuan", 5);
    g.add_a_Edge("Dhaula Kuan", "Karol Bagh", 9);
    g.add_a_Edge("Karol Bagh", "Connaught Place", 2);
    g.add_a_Edge("Connaught Place", "Lajpat Nagar", 8);
    g.add_a_Edge("Lajpat Nagar", "Nehru Place", 3);
    g.add_a_Edge("Nehru Place", "Greater Kailash", 4);

    std::cout << "\n\t\t\t****WELCOME TO THE METRO APP*****" << std::endl;
    while (true) {
        std::cout << "\t\t\t\t~~LIST OF ACTIONS~~\n\n";
        std::cout << "1. LIST ALL THE STATIONS IN THE MAP\n";
        std::cout << "2. SHOW THE METRO MAP\n";
        std::cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION AND THE PATH\n";
        std::cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        std::cout << "5. GET THE MINIMUM DISTANCE YOU NEED TO COVER FROM YOUR 'SOURCE' STATION TO ALL OTHER METRO STATIONS\n";
        std::cout << "6. EXIT THE MENU\n";
        std::cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 7): ";
        int choice;
        std::cin >> choice;

        if (choice == 6) {
            std::cout << "Thanks for using the app" << std::endl;
            break;
        }

        std::string source, destination;
        int isNight, min_time;
        switch (choice) {
            case 1:
                g.display_the_Map();
                break;

            case 2:
                g.print_station_Codelist();
                break;

            case 4:
                std::cout << "ENTER THE SOURCE STATION: ";
                std::cin.ignore();  // Ignore any remaining newline character in the input buffer
                std::getline(std::cin, source);
                std::cout << "ENTER THE DESTINATION STATION: ";
                std::getline(std::cin, destination);
                std::cout << "ENTER 1 FOR DAY OR 0 FOR NIGHT: ";
                std::cin >> isNight;

                if (!g.check_containsVertex(source) || !g.check_containsVertex(destination)) {
                    std::cout << "Invalid source or destination station" << std::endl;
                }
                min_time = g.dijkstra(source, destination, isNight);
                if (min_time != 0) {
                    std::cout << "Minimum Time: " << min_time << " minutes" << std::endl;
                } else {
                    std::cout << "No path found between source and destination!" << std::endl;
                }
                break;

            case 3:
                std::cout << "ENTER THE SOURCE STATION: ";
                std::cin.ignore();  // Ignore any remaining newline character in the input buffer
                std::getline(std::cin, source);
                std::cout << "ENTER THE DESTINATION STATION: ";
                std::getline(std::cin, destination);
                std::cout << "ENTER 1 FOR DAY OR 0 FOR NIGHT: ";
                std::cin >> isNight;

                if (!g.check_containsVertex(source) || !g.check_containsVertex(destination)) {
                    std::cout << "Invalid source or destination station" << std::endl;
                }
                std::cout << "Minimum Distance: " << g.getMinimumDistance(source, destination) << std::endl;
                break;

            case 5:
                std::cout << "ENTER THE SOURCE STATION: ";
                std::cin.ignore();  // Ignore any remaining newline character in the input buffer
                std::getline(std::cin, source);
                if (!g.check_containsVertex(source)) {
                    std::cout << "Invalid source or destination station" << std::endl;
                }
                g.findMinimumSpanningTree(source);
                break;
        }
    }

    return 0;
}
