#include <terrain.h>

int TerrainMesh::get_vertices_size() const {
    return m_vertices.size() * sizeof(float);
}

int TerrainMesh::get_indicies_size() const {
    return m_indicies.size();
}

TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, double scale) 
		: m_gen { gen }
		, m_width { width + 1 }
		, m_height { height + 1 }
		, m_scale { scale }
		, m_vertices ( m_width * m_height * 3 )
		, m_indicies ( width * height  * 6 )
		, m_surface_normals (m_indicies.size())
{
		generate_buffers();

		// generating objects for the vertices
		glGenVertexArrays(1, &m_VAO);

		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), 
				m_vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicies.size() * sizeof(unsigned),
				m_indicies.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glBindVertexArray(0);

		// generating surface normal buffers
		glGenVertexArrays(1, &m_surf_VAO);

		glGenBuffers(1, &m_surf_VBO);

		glBindBuffer(GL_ARRAY_BUFFER, m_surf_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_surface_normals.size(), 
			m_surface_normals.data(), GL_STATIC_DRAW);

		glBindVertexArray(m_surf_VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glBindVertexArray(0);
}

void TerrainMesh::generate_buffers() 
{
    unsigned vert_count = 0;
    double distance = 0.10;
    double z_beg = -0.90;

    double big = 0.0;
    double small = std::numeric_limits<float>::infinity();
    for (int i = 0; i < m_width; ++i) {
        double x_beg = -0.90;

        for (int j = 0; j < m_height; ++j) {
            double height = util::fbm(m_gen, static_cast<double>(i) / m_scale, static_cast<double>(j) / m_scale);
           // double height = m_gen.get_value(static_cast<float>(i) / m_scale, static_cast<float>(j) / m_scale);
            big = std::max(big, height);
            small = std::min(small, height);
            m_vertices[vert_count++] = x_beg;
            m_vertices[vert_count++] = height;
            m_vertices[vert_count++] = z_beg;
            x_beg += distance;
        }

        z_beg += distance;
    }

    unsigned ind_count = 0;
    for (int i = 0; i < m_width - 1; ++i) {
        for (int j = 0; j < m_height - 1; ++j) {
            m_indicies[ind_count++] = i * m_width + j;
            m_indicies[ind_count++] = i * m_width + j + m_width;
            m_indicies[ind_count++] = i * m_width + j + m_width + 1;

            m_indicies[ind_count++] = i * m_width + j;
            m_indicies[ind_count++] = i * m_width + j + m_width + 1;
            m_indicies[ind_count++] = i * m_width + j + 1;
        }
    }

		printf("debuf %lu \n", m_indicies.size());
	unsigned surf_norm_index = 0;
	for (int i = 0; i < m_indicies.size(); i += 3) {
		glm::vec3 triangle_points[3];


		for (int j = 0; j < 3; ++j) {
			triangle_points[j] = glm::vec3(
				m_vertices[m_indicies[i + j]],	
				m_vertices[m_indicies[i + j] + 1],	
				m_vertices[m_indicies[i + j] + 2]);	
				printf("debug %d\n", j);
		}

		glm::vec3 normal = glm::normalize(glm::cross(
			triangle_points[1] - triangle_points[0], 
			triangle_points[2] - triangle_points[1]));
	

		m_surface_normals[surf_norm_index++] = normal[0];	
		m_surface_normals[surf_norm_index++] = normal[1];	
		m_surface_normals[surf_norm_index++] = normal[2];	
	printf("-----debug\n");
	}
}

