#pragma once

#include "EditorWindow.h"

#include "Models/3DModels/Model3D.h"

class WindowModel3D : public EditorWindow
{
public:
	WindowModel3D();
	~WindowModel3D();

	inline void SetModel(const Model3D* i_model) {
		m_model = i_model;
	}

protected:
	void DrawWindowContents() override;

private:
	const std::string& FormatFloat3AsString(const float3& i_point) const;

	const Model3D* m_model = nullptr;
};

