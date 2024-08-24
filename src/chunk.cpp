#include "chunk.h"

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
    set_normals();

    // creating buffers
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
}

Chunk& Chunk::operator=(Chunk&& rhs) noexcept {
    if (this != &rhs) {
        vertices = std::exchange(rhs.vertices, std::vector<Vertex> {});

        m_params = rhs.m_params;

        VAO = rhs.VAO;
        EBO = rhs.EBO;
        VBO = rhs.VBO;
    }

    return *this;
}

void Chunk::regenerate(const TerrainParams& params)
{
    m_params = params;

    vertices = generate_vertices();
    set_normals();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
}

void Chunk::set_normals()
{
    std::vector<int> normal_count(vertices.size());

    for (size_t i = 0; i < indicies.size(); i += 3) {
        Vertex& a = vertices[indicies[i]];
        Vertex& b = vertices[indicies[i + 1]];
        Vertex& c = vertices[indicies[i + 2]];

        const glm::vec3 normal = glm::normalize(glm::cross(
            (b.position - a.position),
            (c.position - a.position)));

        a.normal += normal;
        b.normal += normal;
        c.normal += normal;

        normal_count[indicies[i]]++;
        normal_count[indicies[i + 1]]++;
        normal_count[indicies[i + 2]]++;
    }

    for (size_t i = 0; i < normal_count.size(); ++i) {
        vertices[i].normal = glm::normalize(vertices[i].normal 
                / static_cast<float>(normal_count[i]));
    }
}

std::vector<Vertex> Chunk::generate_vertices()
{
    std::vector<Vertex> heightmap((CHUNK_SIDE + 1) * (CHUNK_SIDE + 1));
    
    int idx = 0;
    float z_pos = m_begin_coords[1];

    for (size_t i = 0; i < CHUNK_SIDE + 1; ++i) {
        float x_pos = m_begin_coords[0];
        for (size_t j = 0; j < CHUNK_SIDE + 1; ++j) {
            const auto mesh_x = static_cast<float>(j + CHUNK_SIDE * m_chunk_id[0]);
            const auto mesh_y = static_cast<float>(i + CHUNK_SIDE * m_chunk_id[1]);

            heightmap[idx++].position = glm::vec3(
                    x_pos, util::fbm(m_gen, mesh_x, mesh_y, m_params), z_pos);

            x_pos += 0.1f;
        }

        z_pos += 0.1f;
    }

    return heightmap;
}

std::vector<unsigned> Chunk::generate_indicies()
{
    std::vector<unsigned> indicies;
    indicies.reserve(CHUNK_SIZE * 6);

    static constexpr size_t offsets[] = {
        0, CHUNK_SIDE + 1, CHUNK_SIDE + 2, 0, CHUNK_SIDE + 2, 1
    };

    for (size_t i = 0; i < CHUNK_SIDE; ++i) {
        for (size_t j = 0; j < CHUNK_SIDE; ++j) {
            auto base = i * (CHUNK_SIDE + 1) + j;

            std::transform(
                std::begin(offsets), 
                std::end(offsets), 
                std::back_inserter(indicies),
                [base](auto offset) { return offset + base; }
            );
        }
    }

    return indicies;
}
