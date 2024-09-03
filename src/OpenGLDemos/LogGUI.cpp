#include "LogGUI.h"

void LogGUI::Log(const char* format, ...)
{
  int old_size = _log_buffer.size();
  va_list args;

  va_start(args, format);
  _log_buffer.appendfv(format, args);
  va_end(args);

  for (int new_size = _log_buffer.size(); old_size < new_size; old_size++)
  {
    if (_log_buffer[old_size] == '\n')
    {
      _line_offsets.push_back(old_size);
    }
  }
  _scroll_bottom = true;
}

void LogGUI::Render(const char* title, bool* p_opened /*= NULL*/)
{
  ImGui::SetNextWindowSize(ImVec2(500, 300));
  ImGui::Begin(title, p_opened);
  if (ImGui::Button("Clear"))
  {
    Clear();
  }

  ImGui::SameLine();
  bool copy = ImGui::Button("Copy");
  ImGui::SameLine();
  _filter.Draw("Filter", -100.0f);

  ImGui::Separator();
  ImGui::BeginChild("scrolling");
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
  if (copy)
  {
    ImGui::LogToClipboard();
  }

  if (_filter.IsActive())
  {
    const char* buffer_begin = _log_buffer.begin();
    const char* line = buffer_begin;
    for (int line_no = 0; line != NULL; line_no++)
    {
      const char* line_end = (line_no < _line_offsets.Size) ? buffer_begin + _line_offsets[line_no] : NULL;
      if (_filter.PassFilter(line, line_end))
      {
        ImGui::TextUnformatted(line, line_end);
      }

      line = line_end && line_end[1] ? line_end + 1 : NULL;
    }
  }
  else
  {
    ImGui::TextUnformatted(_log_buffer.begin());
  }

  if (_scroll_bottom)
  {
    ImGui::SetScrollHereY(1.0f);
  }

  _scroll_bottom = false;
  ImGui::PopStyleVar();
  ImGui::EndChild();
  ImGui::End();
}

void LogGUI::Clear()
{
  _log_buffer.clear();
  _line_offsets.clear();
}
