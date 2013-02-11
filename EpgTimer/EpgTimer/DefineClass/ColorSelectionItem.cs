using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Markup;

namespace EpgTimer
{
    class ColorSelectionItem
    {
        private SolidColorBrush color;
        private string colorName;

        public ColorSelectionItem(string ColorName, SolidColorBrush c)
        {
            color = c;
            colorName = ColorName;
        }
        /// <summary>
        /// return the name of a color
        /// </summary>
        /// <returns></returns>
        public string ColorName
        {
            get { return colorName; }
        }
        /// <summary>
        /// Return the color as a solid colorBrush
        /// </summary>
        public SolidColorBrush Color
        {
            get
            {
                return color;
            }
        }
    }
}
