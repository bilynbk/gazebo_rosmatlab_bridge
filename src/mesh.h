#ifndef GCOP_MESH_H
#define GCOP_MESH_H

namespace gcop {

  /**
   * (Mesh STL).
   * 
   * Author: Marin Kobilarov -- Copyright (C) 2004
   */
  class Mesh {
  public:
    Mesh();

    /**
     * Initialize the Mesh using a PPM file.
     * @param fname name of PPM file
     * @param cs cell size
     * @param ds data size
     * @param o origin - a 3x1 array (optional)
     */
    Mesh(const char *fname, const double *o = 0, const double *scale = 0);

    /**
     * Initialize an empty (flat) Mesh with predefined width and height
     * @param w width
     * @param h height
     * @param cs cell size
     * @param ds data size
     * @param o origin - a 3x1 array (optional)
       Mesh(double w, double h, double cs = 1.0, double ds = 1.0, const double* o = 0);
     */
    
    /**
     * Copy construcor
     * @param mesh DEM
       Mesh(const Mesh &mesh);
     */
    
    virtual ~Mesh();

    /**
     * Is point (x,y) valid, i.e. within the map bounds
     * @param x x-position
     * @param y y-position
     * @return true if valid
     */
    virtual bool IsValid(double x, double y) const;

    /**
     * Get evelation at point (x,y)
     * @param x x-coordinate
     * @param y y-coordinate
     * @return height
     */
    virtual double Get(double x, double y) const;

    /**
     * Give both the elevation and the normal n at point (x,y)
     * @param n normal 
     * @param x x-coordinate
     * @param y y-coordinate
     * @return z-coordinate (elevation)
     */
    double GetNormal(double n[3], double x, double y) const;

    /**
     * Return pointer to the normal at point (x,y)
     * @param x x-coordinate
     * @param y y-coordinate
     * @return pointer to normal
     */
    const double* GetNormal(double x, double y) const;

    /**
     * Get point p=(x,y,z) corresponding to indices (i,j)
     * @param p point 3x1 array
     * @param i i-index
     * @param j j-index
     */
    virtual void Get(double *p, int i, int j) const;    

    /**
     * Set height at point at index (i,j)
     * @param i i-index
     * @param j j-index
     * @param z height
     */
    void Set(int i, int j, double z);

    /**
     * Set height at point (x,y)
     * @param x x-coordinate
     * @param y y-coordinate
     * @param z height
     * @param s size of point - optionally instead of setting single point one case
     *                          set a square of points to height z, effectively 
     *                          creating a prallellepiped at point (x,y) with side s and 
     *                          height z
     */
    void Set(double x, double y, double z, double s = 0);    

    /**
     * Clears the whole mesh
     */
    void Clear();

    void Scale(double s);

    /**
     * Checks if point (x,y,z) is insize (under the surface) of the Mesh
     * @param x x-coordinate
     * @param y y-coordinate
     * @param z z-coordinate
     * @return true if Get(x,y) > z
     */
    bool Inside(double x, double y, double z) const;

    /**
     * Load the Mesh from a PPM file
     * @param fname file name
     */
    void Load(const char *fname);

    /**
     * Get the normal at point (i,j)
     * @param i i-index
     * @param j j-index
     * @return pointer to 3x1 array with the normal vector
     */
    const double* GetNormal(int i, int j) const;

    /**
     * Compute all normals once the Mesh is loaded and ready
     */ 
    void ComputeNormals();

    /**
     * Helper for interpolation
     */
    static double bilinterp(const double* z, int w, int h, double xi, double yi, double eps = 1e-10);

    /**
     * Dilate the DEM
     * @param r distance (radius of ball, or half side-length of cube)
     * @param cube whether to use cube or ball
     */
    void Dilate(double r, bool cube = true);
    
    /**
     * Adds a boundary of height h around the whole Mesh
     * @param h height
     */
    void AddBoundary(double h);

    /**
     *  Apply Gaussian convolution filter with std deviation sigma
     *  @param sigma standard deviation (sigma=0) has no effect
     *  @param cn flag to recompute normals 
     *         (set to false in order to speedup processing when 
     *          computing normals is not necessary)
     *  @param only consider values above thresh
     */
    void Convolve(double sigma, bool cn = true, double thresh = 0);


    double w;          ///< width
    double h;          ///< height
    double o[3];       ///< origin
    double scale[3];   ///< Scale of STL file
    int ni;            ///< number of rows
    int nj;            ///< number of columns
    double *data;      ///< raw data (could be postprocessed)
    //double *odata;     ///< original raw data 
        
    double *normals;   ///< normals    

    double eps;        ///< numerical tolerance for interpolation
  };


  inline bool Mesh::IsValid(double x, double y) const
    {
      return 
        x - o[0] >= -eps && x - o[0] <= w + eps && 
        y - o[1] >= -eps && y - o[1] <= h + eps;
    }
  
};



#endif
