#include "chunk.hpp"

#include <glm/gtx/string_cast.hpp>
#include <iterator>

Chunk::Chunk(NoiseGenerator& gen, const glm::dvec2& coords,
             const glm::vec2& begin, const TerrainParams& params)
    : m_gen{gen}
    , m_params{params}
    , m_begin_coords{begin}
    , m_chunk_id{coords}
    , indicies{generate_indicies()}
    , vertices{generate_vertices()}
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
        vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * indicies.size(), 
        indicies.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
}

void Chunk::regenerate(const TerrainParams& params)
{
    m_params = params;
    vertices = generate_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
}

void Chunk::set_normals(std::vector<Vertex> &vertices, std::vector<uint> const &indicies)
{
    accumulate_vertex_normals(vertices, indicies);
    normalize_vertex_normals(vertices);
}

void Chunk::accumulate_vertex_normals(std::vector<Vertex> &vertices, std::vector<uint> const &indicies)
{
    for (size_t i = 0; i < indicies.size(); i += 3) {
        Vertex& a = vertices[indicies[i]];
        Vertex& b = vertices[indicies[i + 1]];
        Vertex& c = vertices[indicies[i + 2]];

        auto normal = glm::normalize(glm::cross(
            (b.position - a.position), (c.position - a.position)));

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

std::vector<Vertex> Chunk::generate_vertices()
{
    std::vector<Vertex> heightmap;
    heightmap.reserve((CHUNK_SIDE + 1) * (CHUNK_SIDE + 1));
    
    float z_pos = m_begin_coords[1];

    for (size_t i = 0; i < CHUNK_SIDE + 1; ++i) {

        float x_pos = m_begin_coords[0];
        for (size_t j = 0; j < CHUNK_SIDE + 1; ++j) {
            const auto mesh_x = static_cast<float>(j + CHUNK_SIDE * m_chunk_id[0]);
            const auto mesh_y = static_cast<float>(i + CHUNK_SIDE * m_chunk_id[1]);

            heightmap.emplace_back(glm::vec3(
                x_pos, util::fbm(m_gen, mesh_x, mesh_y, m_params), z_pos));

            x_pos += 0.1f;
        }

        z_pos += 0.1f;
    }

    set_normals(heightmap, indicies);
    return heightmap;
}

std::vector<uint> Chunk::generate_indicies()
{
    std::vector<unsigned> indicies;
    indicies.reserve(CHUNK_SIZE * 6);

    static constexpr size_t offsets[] = {
        0, CHUNK_SIDE + 1, CHUNK_SIDE + 2, 0, CHUNK_SIDE + 2, 1
    };

    for (size_t i = 0; i < CHUNK_SIDE; ++i) {
        for (size_t j = 0; j < CHUNK_SIDE; ++j) {
            auto base = i * (CHUNK_SIDE + 1) + j;

            std::transform(std::begin(offsets), std::end(offsets), 
                std::back_inserter(indicies),
                [base](auto offset) { return offset + base; }
            );
        }
    }

    return indicies;
}

