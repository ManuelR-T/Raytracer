/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** define
*/

#pragma once

/**
 * @file define.h
 * @brief This file contains the definitions of success and failure codes, as
 * well as an unused attribute macro.
 */

#define SUCCESS 0  /**< Success code */
#define FAILURE 84 /**< Failure code */
#define UNDEFINED_FD -1

#if defined(__GNUC__) || defined(__clang__)
    #define UNUSED __attribute__((unused)) /**< Macro to mark vars as unused */
#else
    #define UNUSED /**< Macro to mark vars as unused */
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define PACKED __attribute__((packed)) /**<Macro to mark struct as packed*/
#else
    #define PACKED /**< Macro to mark structures as packed */
#endif
