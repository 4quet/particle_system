/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:48:41 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/21 10:58:52 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENGL_PS_HPP
# define OPENGL_PS_HPP

class	OpenGL {
	private:
		GLuint	vao;

	public:
		GLuint	pos_vbo;
		GLuint	vel_vbo;

		OpenGL();

		void	initVBOs();
		void	initVAO();
		void	render();

		float	getXCoord(unsigned int x);
		float	getYCoord(unsigned int y);

		~OpenGL();
};

#endif
