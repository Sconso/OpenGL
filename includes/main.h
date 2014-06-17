/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/17 23:00:51 by sconso            #+#    #+#             */
/*   Updated: 2014/06/17 23:02:27 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct		s_vertex
{
	float			x;
	float			y;
	float			z;
}					t_vertex;

typedef struct		s_cam
{
	t_vertex		pos;
	t_vertex		point;
	t_vertex		tilt;
}					t_cam;

#endif
