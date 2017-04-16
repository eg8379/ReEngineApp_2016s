#pragma once

class BoManager {
	static BoManager* instance;

private:
	BoManager() {};
	BoManager(BoManager const& other) {
		
	};
	BoManager& operator=(BoManager const& other) {

	};

public:
	static BoManager* GetInstance() {
		if (instance == nullptr)
			instance = new BoManager();
		return instance;
	}
	static void ReleaseInstance() {
		if (instance != nullptr) {
			delete instance;
			instance = nullptr;
		}
	}
};