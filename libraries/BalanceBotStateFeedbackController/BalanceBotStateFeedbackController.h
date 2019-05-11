#ifndef BALANCEBOTSTATEFEEDBACKCONTROLLER_H
#define BALANCEBOTSTATEFEEDBACKCONTROLLER_H

class BalanceBotStateFeedbackController{
  private:
  	float k1;
  	float k2;
  	float k3;
  	float k4;
  	
  public:
  	BalanceBotStateFeedbackController();
  	void SetK(float k1, float k2, float k3, float k4);
  	float Update(float psi, float psid, float theta, float thetad);
};

#endif //BALANCEBOTSTATEFEEDBACKCONTROLLER_H
