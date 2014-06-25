/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Board.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 13:14:06 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/06/20 14:25:41 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOARD_H
# define BOARD_H

class Board
{
	public :

	Board(int width, int height);
	int getWidth() const;
	int getHeight() const;

	private :

	int m_width;
	int m_height;
};

#endif
