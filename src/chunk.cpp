#include "chunk.h"

Chunk::Chunk(FBM const &noise, glm::dvec2 const &coords,
             glm::vec2 const &begin, TerrainParams &params)
    : _noise{noise}
    , _params{params}
    , _x_beg{begin[0]}
    , _z_beg{begin[1]}
    , _chunk_id{coords}
    , _indicies{generate_indicies(CHUNK_SIDE)}
    , _vertices{generate_vertices(CHUNK_SIDE)}
{
    // creating buffers
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _vertices.size(),
			_vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * _indicies.size(), 
            _indicies.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
}

void Chunk::regenerate(const TerrainParams& params)
{
    _params = params;
    _vertices = generate_vertices(CHUNK_SIDE);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), _vertices.data(), GL_DYNAMIC_DRAW);
}

glm::vec3 get_triangle_normal(Vertex const &a, Vertex const &b, Vertex const &c)
{
    return glm::normalize(glm::cross((b.position - a.position), (c.position - a.position)));
}

void Chunk::set_normals(std::vector<Vertex> &vertices, std::vector<int> const &indicies)
{
    add_vertex_normals(vertices, indicies);
    normalize_vertex_normals(vertices);
}

void Chunk::add_vertex_normals(std::vector<Vertex> &vertices, std::vector<int> const &indicies)
{
    for (size_t i = 0; i < indicies.size(); i += 3) {
        Vertex& a = vertices[indicies[i]];
        Vertex& b = vertices[indicies[i + 1]];
        Vertex& c = vertices[indicies[i + 2]];

        auto normal = get_triangle_normal(a, b, c);

        a.normal += normal;
        b.normal += normal;
        c.normal += normal;

        a.normals_count++;
        b.normals_count++;
        c.normals_count++;
    }
}

void Chunk::normalize_vertex_normals(std::vector<Vertex>& vertices)
{
    for (auto& vertex : vertices) {
        vertex.normal = glm::normalize(vertex.normal / static_cast<float>(vertex.normals_count));
    }
}

std::vector<Vertex> Chunk::generate_vertices(size_t chunk_side)
{
    std::vector<Vertex> heightmap;
    heightmap.reserve((chunk_side + 1) * (chunk_side + 1));

    float z = _z_beg;
    for (size_t i = 0; i < chunk_side; ++i) {

        float x = _x_beg;
        for (size_t j = 0; j < chunk_side; ++j) {
            float mesh_x = j + chunk_side * _chunk_id[0];
            float mesh_z = i + chunk_side * _chunk_id[1];
            heightmap.emplace_back(glm::vec3(x, _noise.generate(mesh_x, mesh_z), z));

            x += 0.1f;
        }

        z += 0.1f;
    }

    set_normals(heightmap, _indicies);
    return heightmap;
}

std::vector<int> Chunk::generate_indicies(size_t chunk_side)
{
    std::vector<int> indicies;
    indicies.reserve(chunk_side * chunk_side * 6);

    const std::array<size_t, 6> offsets {
        0, chunk_side + 1, chunk_side + 2, 0, chunk_side + 2, 1
    };

    for (size_t i = 0; i < chunk_side; ++i) {
        for (size_t j = 0; j < chunk_side; ++j) {
            size_t base = i * (chunk_side + 1) + j;

            std::transform(begin(offsets), end(offsets), back_inserter(indicies), 
                [base](auto offset) { return offset + base; });
        }
    }

    return indicies;
}

