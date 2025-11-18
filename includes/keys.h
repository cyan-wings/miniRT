/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:04:24 by myeow             #+#    #+#             */
/*   Updated: 2024/08/13 20:06:40 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifndef MINILIBX_KEYS
#  define MINILIBX_KEYS

#  define KEY_A 97
#  define KEY_B 98
#  define KEY_C 99
#  define KEY_D 100
#  define KEY_E 101
#  define KEY_F 102
#  define KEY_G 103
#  define KEY_H 104
#  define KEY_I 105
#  define KEY_J 106
#  define KEY_K 107
#  define KEY_L 108
#  define KEY_M 109
#  define KEY_N 110
#  define KEY_O 111
#  define KEY_P 112
#  define KEY_Q 113
#  define KEY_R 114
#  define KEY_S 115
#  define KEY_T 116
#  define KEY_U 117
#  define KEY_V 118
#  define KEY_W 119
#  define KEY_X 120
#  define KEY_Y 121
#  define KEY_Z 122

#  define KEY_0 48
#  define KEY_1 49
#  define KEY_2 50
#  define KEY_3 51
#  define KEY_4 52
#  define KEY_5 53
#  define KEY_6 54
#  define KEY_7 55
#  define KEY_8 56
#  define KEY_9 57

#  define KEY_ARROW_LEFT 65361
#  define KEY_ARROW_RIGHT 65363
#  define KEY_ARROW_UP 65362
#  define KEY_ARROW_DOWN 65364

#  define KEY_SPACE 32
#  define KEY_ESC 65307
#  define KEY_TAB 65289

#  define MOUSE_LEFT 1
#  define MOUSE_RIGHT 3
#  define MOUSE_MID 2
#  define MOUSE_SCRUP 4
#  define MOUSE_SCRDN 5

#  define ON_KEYDOWN 2
#  define ON_KEYUP 3
#  define ON_DESTROY 17

#  define KEY_PRESS_MASK (1L<<0)
#  define KEY_RELEASE_MASK (1L<<1)
#  define NO_EVENT_MASK 0L

# endif
#endif
