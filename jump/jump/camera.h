class Camera {
	private:
		double cx, cy, cz;

	public:
		Camera();
		Camera(double x, double y, double z);
		double getCx();
		double getCy();
		double getCz();
		void follow1(double bx, double by, double bz);
		void follow3(double bx, double by, double bz);
};
