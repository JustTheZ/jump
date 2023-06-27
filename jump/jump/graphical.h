class Graphical {
	private:
		double gx,gy,gz;
		float color[3];
		int num; //图形编号

	public:
		Graphical();
		void theThree(double x, double z);
		double getGx();
		double getGz();
		void rectangle(); //矩形 1
		void triangle();  //三角形 4 
		void circular(); // 圆形 3
		void square(); // 正方形 2
		void positionRandom();
		void changeModel(Graphical* p);
		static void exchange(Graphical* p, Graphical* q);
		int build();
};
