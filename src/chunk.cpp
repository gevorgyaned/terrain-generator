#include "chunk.hpp"

Chunk::Chunk(SP<FBM> fbm, const glm::dvec2& coords, const glm::vec2& begin) : 
    m_fbm(fbm), m_begin_coords(begin), m_position(coords), 
    m_indicies(generate_indicies()), m_vertices(generate_vertices())
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(),
        m_vertices.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * m_indicies.size(), 
        m_indicies.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
}

void Chunk::draw(Shader shader) const
{
    shader.use();
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indicies.size(), GL_UNSIGNED_INT, (void*)0);
}

void Chunk::update()
{
    m_vertices = generate_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), 
        m_vertices.data(), GL_DYNAMIC_DRAW);
}

void Chunk::set_normals(std::vector<Vertex> &vertices, std::vector<uint> const &indicies)
{
    accumulate_vertex_normals(vertices, indicies);
    normalize_vertex_normals(vertices);
}

void Chunk::accumulate_vertex_normals(std::vector<Vertex> &m_vertices, std::vector<uint> const &m_indicies)
{
    for (size_t i = 0; i < m_indicies.size(); i += 3) {
        Vertex& a = m_vertices[m_indicies[i]];
        Vertex& b = m_vertices[m_indicies[i + 1]];
        Vertex& c = m_vertices[m_indicies[i + 2]];

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

void Chunk::normalize_vertex_normals(std::vector<Vertex>& m_vertices)
{
    for (auto& vertex : m_vertices) {
        vertex.normal = glm::normalize(vertex.normal / (float)vertex.normals_count);
    }
}

std::vector<Vertex> Chunk::generate_vertices()
{
    std::vector<Vertex> heightmap;
    heightmap.reserve((chunk_side + 1) * (chunk_side + 1));
    
    float z_pos = m_begin_coords[1];

    for (size_t i = 0; i < chunk_side + 1; ++i) {

        float x_pos = m_begin_coords[0];
        for (size_t j = 0; j < chunk_side + 1; ++j) {

            float mesh_x = j + chunk_side * m_position[0];
            float mesh_y = i + chunk_side * m_position[1];

            heightmap.emplace_back(glm::vec3(
                x_pos, m_fbm->generate(mesh_x, mesh_y), z_pos));

            x_pos += 0.1f;
        }

        z_pos += 0.1f;
    }

    set_normals(heightmap, m_indicies);
    return heightmap;
}

std::vector<uint> Chunk::generate_indicies()
{
    std::vector<unsigned> m_indicies;
    m_indicies.reserve(chunk_side * chunk_side * 6);

    static constexpr size_t offsets[] = {
        0, chunk_side + 1, chunk_side + 2, 0, chunk_side + 2, 1
    };

    for (size_t i = 0; i < chunk_side; ++i) {
        for (size_t j = 0; j < chunk_side; ++j) {
            auto base = i * (chunk_side + 1) + j;

            std::transform(std::begin(offsets), std::end(offsets), 
                std::back_inserter(m_indicies),
                [base](auto offset) { return offset + base; }
            );
        }
    }

    return m_indicies;
}

