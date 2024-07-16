#include <chunk.h>

#include <iostream>

Chunk::Chunk(NoiseGenerator& gen, const glm::dvec2& coords,
        const glm::vec2& begin, float scale)
    : m_scale { scale }
    , m_begin_coords { begin }
    , m_chunk_id { coords }
{
    generate_vertices(gen);
    generate_normals();

    // creating buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &mesh_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<float>) * m_vertices.size(),
			m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// generating surface normal buffers
    glGenBuffers(1, &normals_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<float>) * m_normals.size(), 
            m_normals.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

template <typename T>
void print(const T& t) {
    for (const auto& x : t) {
        std::cout << x << '\n';
    }
}

Chunk& Chunk::operator=(Chunk&& rhs) noexcept {
    m_vertices = std::exchange(rhs.m_vertices, std::vector<Vertex<float>> {});
    m_normals = std::exchange(rhs.m_normals, std::vector<Vertex<float>> {}); 

    m_scale = std::exchange(rhs.m_scale, 0.0);
    m_begin_coords = std::exchange(rhs.m_begin_coords, glm::vec2());
    m_chunk_id = std::exchange(rhs.m_chunk_id, glm::dvec2());

    m_VAO = std::exchange(rhs.m_VAO, 0);    
    mesh_VBO = std::exchange(rhs.mesh_VBO, 0);
    normals_VBO = std::exchange(rhs.normals_VBO, 0);

    return *this;
}

std::vector<Vertex<float>> Chunk::create_heightmap(NoiseGenerator& gen)
{
    // calculation of the vertex quantity
    std::vector<Vertex<float>> heightmap(pow(CHUNK_SIDE + 1, 2));
    
    size_t vert_count = 0;
    float z_pos = m_begin_coords[1];

    for (size_t i = 0; i < CHUNK_SIDE + 1; ++i) {
        float x_pos = m_begin_coords[0];
        for (size_t j = 0; j < CHUNK_SIDE + 1; ++j) {
            const auto mesh_x = (float)(j + CHUNK_SIDE * m_chunk_id[0]) / m_scale;  
            const auto mesh_y = (float)(i + CHUNK_SIDE * m_chunk_id[1]) / m_scale;  

            heightmap[vert_count++] = Vertex<float>(
                x_pos, 
                util::fbm(gen, mesh_x, mesh_y) + 0.5,
                z_pos);
            x_pos += 0.1f;
        }

        z_pos += 0.1f;
    }

    // std::cout << "cap - " << heightmap.capacity() << "\nvert_count - " << vert_count << std::endl;
    // print(heightmap);

    return heightmap;
}

void Chunk::generate_vertices(NoiseGenerator& gen)
{
    const auto heightmap = create_heightmap(gen);

    std::cout << "size: " << heightmap.size() << std::endl;

    static constexpr size_t add_values[] = { 0, CHUNK_SIDE + 1, CHUNK_SIDE + 2, 0, CHUNK_SIDE + 2, 1};
    for (size_t i = 0; i < CHUNK_SIDE; ++i) {
        for (size_t j = 0; j < CHUNK_SIDE; ++j) {
            for (const auto add_value : add_values) {
                const auto base_index = i * (CHUNK_SIDE + 1) + j;
                m_vertices.push_back(heightmap[base_index + add_value]);
                std::cout << "ind: " << base_index + add_value << std::endl;
            }
        }
    }
    //std::cout << m_vertices.size() << ", " << ind_count << std::endl;

    // exit(0);

    //
    // std::cout << "cap - " << m_vertices.capacity() << "\nvert_count - " << ind_count << std::endl;
    // exit(0);// exit(0);
}

void Chunk::generate_normals()
{
    size_t surf_norm_index = 0;
    for (size_t i = 0; i < m_vertices.size(); i += 3) {
        glm::vec3 normal = glm::normalize(glm::cross(
            static_cast<glm::vec3>(m_vertices[i + 1] - m_vertices[i]),
            static_cast<glm::vec3>(m_vertices[i + 2] - m_vertices[i])));

        const Vertex vert(normal[0], normal[1], normal[2]);

        m_normals[surf_norm_index++] = vert;	
        m_normals[surf_norm_index++] = vert;	
        m_normals[surf_norm_index++] = vert;	
    }
}
