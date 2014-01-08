/*!
 * \file definition_structure.hpp
 * \brief Headers of the main subroutines used by SU2_CFD.
 *        The subroutines and functions are in the <i>definition_structure.cpp</i> file.
 * \author Aerospace Design Laboratory (Stanford University) <http://su2.stanford.edu>.
 * \version 1.0.0
 *
 * Stanford University Unstructured (SU2).
 * Copyright (C) 2012-2013 Aerospace Design Laboratory (ADL).
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifndef NO_MPI
#include <mpi.h>
#endif
#include <ctime>

#include "solver_structure.hpp"
#include "integration_structure.hpp"
#include "output_structure.hpp"
#include "numerics_structure.hpp"
#include "geometry_structure.hpp"
#include "config_structure.hpp"

using namespace std;

/*! 
 * \brief Gets the number of dimensions in the mesh file
 * \param[in] val_mesh_filename - Name of the file with the grid information.
 * \param[in] val_format - Format of the file with the grid information.
 * \return Total number of dimesions in the grid file.
 */
unsigned short GetnDim(string val_mesh_filename, unsigned short val_format);


/*! 
 * \brief Definition and allocation of all solution classes.
 * \param[in] solver_container - Container vector with all the solutions.
 * \param[in] geometry - Geometrical definition of the problem.
 * \param[in] config - Definition of the particular problem.
 */
void Solver_Preprocessing(CSolver ***solver_container, CGeometry **geometry, CConfig *config);

/*! 
 * \brief Definition and allocation of all integration classes.
 * \param[in] integration_container - Container vector with all the integration methods.
 * \param[in] geometry - Geometrical definition of the problem.
 * \param[in] config - Definition of the particular problem.
 */
void Integration_Preprocessing(CIntegration **integration_container, CGeometry **geometry, CConfig *config);

/*! 
 * \brief Definition and allocation of all solver classes.
 * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
 * \param[in] solver_container - Container vector with all the solutions.
 * \param[in] geometry - Geometrical definition of the problem.
 * \param[in] config - Definition of the particular problem.
 */
void Numerics_Preprocessing(CNumerics ****numerics_container, CSolver ***solver_container, CGeometry **geometry, CConfig *config);

/*! 
 * \brief Do the geometrical preprocessing.
 * \param[in] geometry - Geometrical definition of the problem.
 * \param[in] config - Definition of the particular problem.
 */
void Geometrical_Preprocessing(CGeometry **geometry, CConfig *config);