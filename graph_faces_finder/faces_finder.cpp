#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

struct HalfEdge;

struct Point 
{
    long double x, y;
    int id_number;
    std::vector<HalfEdge*> connected_edges;

    Point(long double x_, long double y_, int id_number_): x(x_), y(y_), id_number(id_number_) {}

    Point(): x(0), y(0), id_number(0) {}

};

struct HalfEdge 
{
    Point* point1;
    Point* point2;
    HalfEdge* next = nullptr;

    long double polar_angle_rad_12;
    long double polar_angle_rad_21;

    bool visited;

    HalfEdge(Point& point1_, Point& point2_) 
    {
        point1 = &point1_;
        point2 = &point2_;
        visited = false;

        polar_angle_rad_12 = atan2((point2->y - point1->y), (point2->x - point1->x));
        if(polar_angle_rad_12 < 0) 
        {
            polar_angle_rad_12 = polar_angle_rad_12 + 6.28318;
        }

        polar_angle_rad_21 = atan2((point1->y - point2->y), (point1->x - point2->x));
        if(polar_angle_rad_21 < 0) 
        {
            polar_angle_rad_21 = polar_angle_rad_21 + 6.28318;
        }

    }

    HalfEdge(): visited(0) {}

};

void make_faces(HalfEdge& edge) 
{
    if(edge.next != nullptr)
    {
        return;
    }

    HalfEdge* current_edge = &edge;
    int initial_id = edge.point1->id_number;
    
    while(current_edge->next == nullptr) 
    {
        if(current_edge->point2->connected_edges.size() == 1) 
        {
            current_edge->next = current_edge->point2->connected_edges[0];
        }
        else 
        {
            long double delta_smallest = -7;
            if(current_edge->point2->connected_edges[0]->point2->id_number != current_edge->point1->id_number)
            {
                delta_smallest = current_edge->polar_angle_rad_21 - current_edge->point2->connected_edges[0]->polar_angle_rad_12;
            }
            else
            {
                delta_smallest = current_edge->polar_angle_rad_21 - current_edge->point2->connected_edges[1]->polar_angle_rad_12;
            }

            for(int i = 0; i < current_edge->point2->connected_edges.size(); i++) 
            {  
                long double delta = current_edge->polar_angle_rad_21 - current_edge->point2->connected_edges[i]->polar_angle_rad_12;
                if(delta > 0 && delta <= delta_smallest) 
                {
                    current_edge->next = current_edge->point2->connected_edges[i];
                    delta_smallest = delta;
                }
                else if (delta > 0 && delta_smallest < 0 && delta > delta_smallest)
                {
                    current_edge->next = current_edge->point2->connected_edges[i];
                    delta_smallest = delta;  
                }
                else if(delta < 0 && delta_smallest <= 0 && delta <= delta_smallest)
                {
                    current_edge->next = current_edge->point2->connected_edges[i];
                    delta_smallest = delta;
                }
                else if(delta == 0 && delta_smallest < 0 && current_edge->point2->connected_edges[i]->point2->id_number != current_edge->point1->id_number)
                {
                    current_edge->next = current_edge->point2->connected_edges[i];
                    delta_smallest = delta;
                }
            }
        }
        current_edge = current_edge->next;
    }
}

int pos_smallest_element(const std::vector<int>& vec) {
    int minElement = vec[0];
    int minPosition = 0;
    
    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i] < minElement) {
            minElement = vec[i];
            minPosition = i;
        }
    }
    
    return minPosition;
}

std::vector<int> return_face(HalfEdge& edge)
{
    make_faces(edge);

    std::vector<int> face;
    HalfEdge* current_edge = &edge;

    while(!current_edge->visited)
    {
        face.insert(face.begin(), current_edge->point1->id_number);
        current_edge->visited = true;
        current_edge = current_edge->next;      
    }

    std::rotate(face.begin(), face.begin() + pos_smallest_element(face), face.end());

    return face;
}

bool compare_vectors(const std::vector<int>& a, const std::vector<int>& b) {
    return a.size() > b.size();
}

void print_faces(std::vector<HalfEdge*> &edges)
{

    int n_faces = 0;
    std::vector<std::vector<int> > faces;

    for(int i = 0; i < edges.size(); i++)
    {
        HalfEdge* edge = edges[i];

        if (!edge->visited)
        {
            std::vector<int> face = return_face(*edge);
            faces.push_back(face);
            n_faces++;
        }

    }

    std::sort(faces.begin(), faces.end(), compare_vectors);

    std::cout << n_faces << std::endl;

    for (int i = 0; i < faces.size(); i++)
    {
        std::cout << faces[i].size() + 1 << " ";
        for(int j = 0; j < faces[i].size(); j++)
        {
            std::cout << faces[i][j] << " ";
        }
        std::cout << faces[i].front();

        std::cout << std::endl;
    }
}



int main() 
{
    int n_vertices, n_edges;

    std::cin >> n_vertices >> n_edges;

    Point vertices[n_vertices];
    std::vector<HalfEdge*> edges;

    for(int i = 1; i <= n_vertices; i++) 
    {
        long double x, y;
        int vertex_degree;

        std::cin >> x >> y >> vertex_degree;

        Point point(x, y, i);

        vertices[i - 1] = point;

        for(int j = 0; j < vertex_degree; j++) 
        {
            int neighbor_id;
            std::cin >> neighbor_id;
            if(neighbor_id < i)
            {
                HalfEdge* new_edge = new HalfEdge(vertices[i - 1], vertices[neighbor_id - 1]);
                HalfEdge* new_reverse_edge = new HalfEdge(vertices[neighbor_id - 1], vertices[i - 1]);

                edges.push_back(new_edge);
                edges.push_back(new_reverse_edge);

                vertices[i - 1].connected_edges.push_back(new_edge);
                vertices[neighbor_id - 1].connected_edges.push_back(new_reverse_edge);
            }
            
        }

    }

    print_faces(edges);

    for (HalfEdge* edge : edges) {
        delete edge;
    }
    edges.clear();

}