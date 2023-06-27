class Ball {
	private:
		int radius, direction; //°ë¾¶
		float* color;
		double bx, by, bz;

	public:
		Ball();
		Ball(int r,float* c,double x,double y,double z);
		void creatBall();
		void creatHighJumper(int angle);
		void creatTextureBall();
		void colorRandom();
		void selfJump(int &a);
		double getBx();
		double getBy();
		double getBz();
		double jump(double time, double x, double z, int circulate);
};
