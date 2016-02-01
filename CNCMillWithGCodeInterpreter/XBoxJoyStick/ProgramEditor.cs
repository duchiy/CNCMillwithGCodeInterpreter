using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Media;

namespace XBoxJoyStick
{
    public class ProgramEditor
    {
        System.Windows.Controls.RichTextBox _txtProgram = null;

        public void Set(System.Windows.Controls.RichTextBox rtbox)
        {
            _txtProgram = rtbox;
        }
        public string OpenFile()
        {

            OpenFileDialog opentext = new OpenFileDialog();
            if (opentext.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string programName = opentext.FileName;
                using (System.IO.StreamReader sr = new System.IO.StreamReader(programName))
                {

                    Paragraph paragraph = new Paragraph();
                    paragraph.Inlines.Add(sr.ReadToEnd());
                    FlowDocument document = new FlowDocument(paragraph);
                    _txtProgram.Document = document;
                }
                return programName;
            }
            return "";
        }
        public TextRange FindTextInRange(TextRange searchRange, string searchText)
        {
            // Search the text with IndexOf
            int offset = searchRange.Text.IndexOf(searchText);
            int offset1 = searchRange.Text.IndexOf("\r\n", offset);

            if (offset < 0)
                return null;  // Not found

            // Try to select the text as a contiguous range
            TextPointer start = searchRange.Start.GetPositionAtOffset(offset);
            TextPointer end = start.GetPositionAtOffset(offset1 - offset);
            TextRange result = new TextRange(start, end);
            return result;
        }
        public TextRange GetTextRangeAtLine(int line)
        {
            TextRange LineAtTextRange;

            TextPointer startPointer = _txtProgram.Selection.Start.GetLineStartPosition(line);
            if (startPointer == null)
                return null;

            TextPointer endPointer = _txtProgram.Selection.Start.GetLineStartPosition(line + 1);
            if (endPointer == null)
                return null;

            LineAtTextRange = new TextRange(startPointer, endPointer);
            return LineAtTextRange;
        }
        public TextRange DoSearch(System.Windows.Controls.RichTextBox richTextBox, string searchText, int line, out int newline)
        {
            TextRange searchRange;
            newline = line;
            do
            {
                searchRange = GetTextRangeAtLine(line);
                int offset = searchRange.Text.IndexOf(searchText);

                if (offset != -1)
                {
                    return searchRange;
                }

                line++;
                newline = line;

            } while (searchRange != null);

            return null;
        }

        public int SearchAndHighLightLine(int line, string searchText)
        {
            int newLine = 0;
            TextRange newTextRange = DoSearch(_txtProgram, searchText, line, out newLine);
            _txtProgram.ScrollToVerticalOffset(line + 15);
            if (newTextRange != null)
            {
                TextRange previousTextRange = GetTextRangeAtLine(line - 1);
                HighLightLine(previousTextRange, Brushes.White);
                HighLightLine(newTextRange, Brushes.Red);
                line = ++newLine;
            }
            return line;
        }
        public void HighLightLine(TextRange TextRange, Object HightLightColor)
        {
            if (TextRange != null)
            {
                TextRange.ApplyPropertyValue(TextElement.BackgroundProperty, HightLightColor);
            }
        }

    }
}