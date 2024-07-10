#include <terrain.h>

template <typename T>
Vertex<T> operator-(const Vertex<T>& a, const Vertex<T>& b)
{
    return Vertex(b.x - a.x, b.y - a.y, b.z - a.z);
}

int TerrainMesh::get_vertices_size() const {
    return m_vertices.size();
}

TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, double scale) 
	    : m_gen { gen }
		, m_width { width + 1 }
		, m_height { height + 1 }
		, m_scale { scale }
        , m_vertices ( width * height * 6)
        , m_normals ( m_vertices.size() )
{
	generate_buffers();
    
	// generating objects for the vertices
	glGenVertexArrays(1, &m_vertices_VAO);
	glGenBuffers(1, &m_vertices_VBO);

	glBindVertexArray(m_vertices_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex<float>), 
			m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// generating surface normal buffers
    glGenBuffers(1, &m_normal_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_normal_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex<float>) * m_normals.size(), 
            m_normals.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void TerrainMesh::generate_buffers() 
{
    std::vector<Vertex<float>> data(m_width * m_height * 3);
    std::size_t vert_count = 0;
    float z_pos = m_z_beg;

    for (std::size_t i = 0; i < m_width; ++i) {
        float x_pos = m_x_beg;
        for (std::size_t j = 0; j < m_height; ++j) {
            data[vert_count++] = Vertex<float>(
                x_pos, 
                util::fbm(m_gen, static_cast<float>(i) / m_scale, static_cast<float>(j) / m_scale) + 0.5,
                z_pos
            );
            x_pos += m_tile_distance;
        }

        z_pos += m_tile_distance;
    }


    std::size_t ind_count = 0;
    const std::size_t add_values[] = { 0, m_width, m_width + 1, 0, m_width + 1, 1};

    for (std::size_t i = 0; i < m_width - 1; ++i) {
        for (std::size_t j = 0; j < m_height - 1; ++j) {
            for (std::size_t k = 0; k < sizeof(add_values) / sizeof(std::size_t); ++k) {
                m_vertices[ind_count++] = data[i * m_width + j + add_values[k]];
            }
        }
    }

	unsigned surf_norm_index = 0;
	for (std::size_t i = 0; i < m_vertices.size(); i += 3) {
		glm::vec3 normal = glm::normalize(glm::cross(
			(glm::vec3)(m_vertices[i + 1] - m_vertices[i]), 
			(glm::vec3)(m_vertices[i + 2] - m_vertices[i + 1])));
	
        const Vertex vert(normal[0], normal[1], normal[2]);

		m_normals[surf_norm_index++] = vert;	
		m_normals[surf_norm_index++] = vert;	
		m_normals[surf_norm_index++] = vert;	
	}

    for (const auto& v : m_normals) {
        const auto [x, y, z] = v.get_values();
        std::cout << x << ", " << y << ", " << z << std::endl;
    }
}

