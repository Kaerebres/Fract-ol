/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_call.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:14:04 by csimon            #+#    #+#             */
/*   Updated: 2017/06/16 17:14:05 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUDA_CALL_H
# define CUDA_CALL_H
# include <cuda.h>
# include "./minilibx_macos/mlx.h"
# define HANDLE_ERRORJ( err ) (handleerrorj( err, __FILE__, __LINE__ ))
# define HANDLE_ERRORA( err ) (handleerrora( err, __FILE__, __LINE__ ))
# define HANDLE_ERRORM( err ) (handleerrorm( err, __FILE__, __LINE__ ))
# define HANDLE_ERRORS( err ) (handleerrors( err, __FILE__, __LINE__ ))
# define HANDLE_ERRORK( err ) (handleerrork( err, __FILE__, __LINE__ ))

static void	handleerrork(cudaError_t err, const char *file, int line);
static void	handleerrorj(cudaError_t err, const char *file, int line);
static void	handleerrora(cudaError_t err, const char *file, int line);
static void	handleerrorm(cudaError_t err, const char *file, int line);
static void	handleerrors(cudaError_t err, const char *file, int line);

#endif
