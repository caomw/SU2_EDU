/*!
 * \file output_structure.hpp
 * \brief Headers of the main subroutines for generating the file outputs.
 *        The subroutines and functions are in the <i>output_structure.cpp</i> file.
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

#include <fstream>
#include <cmath>
#include <time.h>
#include <fstream>

#include "solver_structure.hpp"
#include "integration_structure.hpp"
#include "geometry_structure.hpp"
#include "config_structure.hpp"

using namespace std;

/*! 
 * \class COutput
 * \brief Class for writing the flow, adjoint and linearized solver 
 *        solution (including the history solution, and parallel stuff).
 * \author F. Palacios, T. Economon, M. Colonno.
 * \version 1.0.0
 */
class COutput {

	unsigned long nGlobal_Poin;   // Global number of nodes with halos
  unsigned long nSurf_Poin;   // Global number of nodes of the surface
  unsigned long nGlobal_Doma;   // Global number of nodes without halos
	unsigned long nGlobal_Elem;  // Global number of elems without halos
  unsigned long nSurf_Elem,  // Global number of surface elems without halos
  nGlobal_Line,
	nGlobal_BoundTria,
	nGlobal_BoundQuad,
	nGlobal_Tria,
	nGlobal_Quad,
	nGlobal_Tetr,
	nGlobal_Hexa,
	nGlobal_Wedg,
	nGlobal_Pyra;
	double **Coords;              // node i (x,y,z) = (Coords[0][i], Coords[1][i], Coords[2][i])
  int *Conn_Line;
  int *Conn_BoundTria;
	int *Conn_BoundQuad;
  int *Conn_Tria;	// triangle 1 = Conn_Tria[0], Conn_Tria[1], Conn_Tria[3]
	int *Conn_Quad;
	int *Conn_Tetr;
	int *Conn_Hexa;
	int *Conn_Wedg;
	int *Conn_Pyra;
	double *Volume;
	double **Data;
	double **residuals, **consv_vars;					// placeholders
	double *p, *rho, *M, *Cp, *Cf, *Ch, *h, *yplus;		// placeholders 
	unsigned short nVar_Consv, nVar_Total, nVar_Extra, nZones;
	bool wrote_base_file, wrote_surf_file, wrote_CGNS_base, wrote_Tecplot_base, wrote_Paraview_base;

  int cgns_base, cgns_zone, cgns_base_results, cgns_zone_results;
  
protected:

public:

  unsigned short **nOutput_Vars;
  double ****data_container;
  
	/*! 
	 * \brief Constructor of the class. 
	 */
	COutput(void);

	/*! 
	 * \brief Destructor of the class. 
	 */
	~COutput(void);

	/*! 
	 * \brief Writes and organizes the all the output files, except the history one, for serial computations.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetResult_Files(CSolver ***solver_container, CGeometry **geometry, CConfig *config, unsigned long iExtIter);
	
  /*!
	 * \brief Writes and organizes the all the output files, except the history one, for serial computations.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetBaselineResult_Files(CSolver *solver, CGeometry *geometry, CConfig *config, unsigned long iExtIter);
  
	/*! 
	 * \brief Writes equivalent area.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetEquivalentArea(CSolver *solver_container, CGeometry *geometry, CConfig *config, 
			unsigned long iExtIter);
	
	/*! 
	 * \brief Create and write the file with the flow coefficient on the surface.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] FlowSolution - Flow solution.
	 * \param[in] iExtIter - Current external (time) iteration.
	 */
	void SetSurfaceCSV_Flow(CConfig *config, CGeometry *geometry, CSolver *FlowSolver, unsigned long iExtIter);

  /*!
	 * \brief Merge the geometry into a data structure used for output file writing.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void MergeConnectivity(CConfig *config, CGeometry *geometry);
  
  /*!
	 * \brief Merge the node coordinates from all processors.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void MergeCoordinates(CConfig *config, CGeometry *geometry);
  
  /*!
	 * \brief Merge the connectivity for a single element type from all processors.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] Elem_Type - VTK index of the element type being merged.
	 */
	void MergeVolumetricConnectivity(CConfig *config, CGeometry *geometry, unsigned short Elem_Type);
  
  /*!
	 * \brief Merge the connectivity for a single element type from all processors.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] Elem_Type - VTK index of the element type being merged.
	 */
	void MergeSurfaceConnectivity(CConfig *config, CGeometry *geometry, unsigned short Elem_Type);
  
	/*!
	 * \brief Merge the solution into a data structure used for output file writing.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solution - Flow, adjoint or linearized solution.
	 */
	void MergeSolution(CConfig *config, CGeometry *geometry, CSolver **solver);
  
  /*!
	 * \brief Write a native SU2 restart file.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void SetRestart(CConfig *config, CGeometry *geometry);
  
  /*!
	 * \brief Write a Paraview ASCII solution file.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void SetParaview_ASCII(CConfig *config, CGeometry *geometry, bool surf_sol);
  
  /*!
	 * \brief Write a Tecplot ASCII solution file.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void SetTecplot_ASCII(CConfig *config, CGeometry *geometry, bool surf_sol);

  /*!
	 * \brief Deallocate temporary memory needed for merging and writing coordinates.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void DeallocateCoordinates(CConfig *config, CGeometry *geometry);
  
  /*!
	 * \brief Deallocate temporary memory needed for merging and writing connectivity.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void DeallocateConnectivity(CConfig *config, CGeometry *geometry, bool surf_sol);
  
  /*!
	 * \brief Deallocate temporary memory needed for merging and writing solution variables.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] geometry - Geometrical definition of the problem.
	 */
	void DeallocateSolution(CConfig *config, CGeometry *geometry);
  
	/*! 
	 * \brief Write the header of the history file.
	 * \param[in] ConvHist_file - Pointer to the convergence history file (which is defined in the main subroutine).
	 * \param[in] config - Definition of the particular problem.
	 */
	void SetHistory_Header(ofstream *ConvHist_file, CConfig *config);

	/*! 
	 * \brief Write the history file and the convergence on the screen for serial computations.
	 * \param[in] ConvHist_file - Pointer to the convergence history file (which is defined in the main subroutine).
	 * \param[in] geometry - Geometrical definition of the problem.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] integration - Generic subroutines for space integration, time integration, and monitoring.
	 * \param[in] iExtIter - Current external (time) iteration.
	 * \param[in] timeused - Current number of clock tick in the computation (related with total time).
	 */
	void SetConvergence_History(ofstream *ConvHist_file, CGeometry **geometry, CSolver ***solver_container, CConfig *config,
                              CIntegration **integration, bool DualTime, double timeused);

};