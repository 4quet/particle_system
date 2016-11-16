/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenCL.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 09:01:24 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/16 17:28:19 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_PS_HPP
# define OPENCL_PS_HPP

class	OpenCL {
	private:
		std::vector<cl::Device>	devices;
		unsigned int			used_device;
		cl_int					error;

	public:
		cl::Context				context;
		cl::CommandQueue		queue;
		cl::Program				program;

		std::vector<cl::Memory>	buffers;

		OpenCL();

		void		loadCLProgram(std::string path);
		std::string	errorString(cl_int error);

		~OpenCL();
};

#endif
