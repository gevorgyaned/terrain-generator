#include <terrain.h>

int TerrainMesh::get_vertices_size() const {
    return m_vertices.size();
}


TerrainMesh::TerrainMesh(NoiseGenerator& gen, std::size_t width, std::size_t height, double scale) 
	    : m_gen { gen }
		, m_width { width + 1 }
		, m_height { height + 1 }
		, m_scale { scale }
        , m_vertices ( width * height * 18)
        , m_normals ( m_vertices.size() )
{
	generate_buffers();
    
	// generating objects for the vertices
	glGenVertexArrays(1, &m_vertices_VAO);
	glGenBuffers(1, &m_vertices_VBO);


	glBindVertexArray(m_vertices_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), 
			m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glBindVertexArray(0);

	// generating surface normal buffers
    glGenVertexArrays(1, &m_normal_VAO);
    glGenBuffers(1, &m_normal_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_normal_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_normals.size(), 
		m_normals.data(), GL_STATIC_DRAW);

	glBindVertexArray(m_normal_VAO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glBindVertexArray(0);
}

void TerrainMesh::generate_buffers() 
{
    std::vector<Vertex<float>> data(m_width * m_height * 3);
    std::size_t vert_count = 0;
    float z = m_z_beg;

    for (std::size_t i = 0; i < m_width; ++i) {
        float x = m_x_beg;
        for (std::size_t j = 0; j < m_height; ++j) {
            data[vert_count++] = Vertex<float>(
                x, 
                util::fbm(m_gen, static_cast<float>(i) / m_scale, static_cast<float>(j) / m_scale) + 0.5,
                z
            );
            x+= m_tile_distance;
        }

        z += m_tile_distance;
    }


    std::size_t ind_count = 0;
    const std::size_t add_values[] = { 0, m_width, m_width + 1, 0, m_width + 1, 1};

    for (std::size_t i = 0; i < m_width - 1; ++i) {
        for (std::size_t j = 0; j < m_height - 1; ++j) {
            for (std::size_t k = 0; k < sizeof(add_values) / sizeof(std::size_t); ++k) {
                auto [x, y, z] = data[i * m_width + j + add_values[k]].get_values();
                m_vertices[ind_count++] = x;
                m_vertices[ind_count++] = y;
                m_vertices[ind_count++] = z;
            }
        }
    }

            //  m_vertices [ind_count++] = data[i * m_width + j];
            //  m_vertices [ind_count++] = data[i * m_width + j + m_width];
            //  m_vertices [ind_count++] = data[i * m_width + j + m_width + 1] ;

            //  m_vertices [ind_count++] = data[i * m_width + j];
            //  m_vertices [ind_count++] = data[i * m_width + j + m_width + 1];
            //  m_vertices [ind_count++] = data[i * m_width + j + 1];
    //for (std::size_t i = 0; i < m_vertices.size(); i += 3) {
    //    printf("%f, %f, %f\n", m_vertices[i], m_vertices[i + 1], m_vertices[i + 2]); 
    //}


	//unsigned surf_norm_index = 0;
    
	//for (std::size_t i = 0; i < m_vertices.size(); i += 3) {
	//	glm::vec3 triangle_points[3];
	//	for (std::size_t j = 0; j < 3; ++j) {
	//		triangle_points[j] = glm::vec3(
	//			m_vertices[m_vertices[i + j]],	
	//			m_vertices[m_vertices[i + j] + 1],	
	//			m_vertices[m_vertices[i + j] + 2]);	
	//			
	//	}

	//	glm::vec3 normal = glm::normalize(glm::cross(
	//		triangle_points[1] - triangle_points[0], 
	//		triangle_points[2] - triangle_points[1]));
	//
	//	m_normals[surf_norm_index++] = normal[0];	
	//	m_normals[surf_norm_index++] = normal[1];	
	//	m_normals[surf_norm_index++] = normal[2];	
	//	m_normals[surf_norm_index++] = normal[0];	
	//	m_normals[surf_norm_index++] = normal[1];	
	//	m_normals[surf_norm_index++] = normal[2];	
	//	m_normals[surf_norm_index++] = normal[0];	
	//	m_normals[surf_norm_index++] = normal[1];	
	//	m_normals[surf_norm_index++] = normal[2];	
	//}

}

