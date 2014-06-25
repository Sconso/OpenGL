// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Camera.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2014/06/24 16:44:33 by Myrkskog          #+#    #+#             //
//   Updated: 2014/06/24 16:44:34 by Myrkskog         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <Render.h>

Camera::Camera()
{
    angle = 0.0f;
    
    posX = 0;
    posY = 0;
    posZ = 50;

    pointX = 0;
    pointY = 0;
    pointZ = 0;

    tiltX = 0;
    tiltY = 1;
    tiltZ = 0;
}