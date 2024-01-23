/*
  --- SIDE BUTTONS ---
  ImGui::SetNextWindowPos(image_pose, ImGuiCond_Always);
  ImGui::SetNextWindowBgAlpha(0.0f);
  ImGuiWindowFlags flags;
  flags |= ImGuiWindowFlags_NoMove;
  flags |= ImGuiWindowFlags_NoTitleBar;
  flags |= ImGuiWindowFlags_NoResize;
  flags |= ImGuiWindowFlags_AlwaysAutoResize;
  flags |= ImGuiWindowFlags_NoSavedSettings;
  flags |= ImGuiWindowFlags_NoFocusOnAppearing;
  flags |= ImGuiWindowFlags_NoNav;
  flags |= ImGuiWindowFlags_NoNavFocus;
  flags |= ImGuiWindowFlags_NoScrollbar;
  flags |= ImGuiWindowFlags_NoDocking;

  if (ImGui::Begin("##osef138", nullptr, flags)){
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##398", ImVec2(25, 25))){
      //k4a_player->rotation(k4n_sensor, 1);
    }
    if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##39sss8", ImVec2(15, 15))){
      //k4a_player->rotation(k4n_sensor, 1);
    }
    if(ImGui::Button(ICON_FA_ARROWS_ROTATE "##39sss8", ImVec2(15, 15))){
      //k4a_player->rotation(k4n_sensor, 1);
    }
    ImGui::PopStyleVar();
  }
  ImGui::End();
*/
