#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

class Site {
public:
	virtual void access()=0;
	virtual void addPage(string)=0;
	virtual ~Site() {
	}
};

class SinglePage: public Site {
	string page;
public:
	SinglePage(string page = "") {
		this->page = page;
	}
	void addPage(string page) {
		this->page = page;
	}
	void access() {
		cout << "Single page site" << endl;
		cout << page << endl;
		cout << endl;
	}
};

class MultiPage: public Site {
	vector<string> pages;
public:
	MultiPage(string page = "") {
		this->pages.push_back(page);
	}
	void addPage(string page) {
		if (this->pages[0] != "")
			this->pages.push_back(page);
		else
			this->pages[0] = page;
	}
	void access() {
		cout << "Multi page site" << endl;
		for (auto page : this->pages)
			cout << page << endl;
		cout << endl;
	}
};

class Coder {
protected:
	Site *site;
	int mood;
public:
	Coder(Site *site) {
		this->site = site;
		this->mood = 0;
	}
	virtual void code()=0;
	virtual ~Coder() {
	}
	friend class Angel;
	friend class Goat;
};

class JavaScriptCoder: public Coder {
public:
	JavaScriptCoder(Site *site) :
			Coder(site) {
	}
	void code() {
		string content = "index.js " + to_string(this->mood);
		this->site->addPage(content);
	}
};

class PHPCoder: public Coder {
public:
	PHPCoder(Site *site) :
			Coder(site) {
	}
	void code() {
		string content = "index.php " + to_string(this->mood);
		this->site->addPage(content);
	}
};

class ProjectManager {
public:
	virtual void interact(Coder*)=0;
	virtual ~ProjectManager() {
	}
};

class Angel: public ProjectManager {
public:
	void interact(Coder *coder) {
		coder->mood += 50;
	}
};

class Goat: public ProjectManager {
public:
	void interact(Coder *coder) {
		coder->mood -= 50;
	}
};

class Project {
	Site *site;
	Coder *coder;
	ProjectManager *leader;

	Project(Site *site, Coder *coder, ProjectManager *leader) {
		this->site = site;
		this->coder = coder;
		this->leader = leader;
	}
public:
	void show() {
		this->site->access();
	}

	friend class ProjectFactory;
};

class ProjectFactory {
public:
	Project* makeRandomProject() {
		Site *site;
		if (rand() % 2)
			site = new SinglePage;
		else
			site = new MultiPage;
		Coder *coder;
		if (rand() % 2)
			coder = new JavaScriptCoder(site);
		else
			coder = new PHPCoder(site);
		ProjectManager *leader;
		if (rand() % 2)
			leader = new Angel;
		else
			leader = new Goat;
		leader->interact(coder);
		coder->code();
		coder->code();
		return new Project(site, coder, leader);
	}
};

int main() {
	srand(time(NULL));
	ProjectFactory *factory = new ProjectFactory;
	Project *p1 = factory->makeRandomProject();
	Project *p2 = factory->makeRandomProject();
	Project *p3 = factory->makeRandomProject();
	p1->show();
	p2->show();
	p3->show();
	return 0;
}
