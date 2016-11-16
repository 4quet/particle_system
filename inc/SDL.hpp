/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:40:40 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/16 17:28:49 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_HPP
# define SDL_HPP

class	SDL {
	private:
		void	initOpenGLWindow();

	public:
		SDL_Window		*win;
		SDL_GLContext	context;

		SDL();
		~SDL();
};

#endif
